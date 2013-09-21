#include <cstdlib>
#include "util/Logger.h"
#include "util/id2Str.h"
#include "executeSolver.h"
#include "problemInstanceFromFiles.h"
#include "solver/clusterAndPickSolver.h"
#include "solver/restrictedHACSolver.h"
#include "solver/randomBOBOSolver.h"
#include "solver/randomSOBOSolver.h"
#include "solver/exhaustiveGreedyAnySimSOBOSolver.h"
#include "solver/exhaustiveGreedySumSimSOBOSolver.h"
#include "solver/sequentialScanSolver.h"
#include "solver/restrictedHACWithSpecificItemSolver.h"

#include <iostream>
using namespace std;

ProblemInstance* instanceTheProblem(ConfigurationJaks& configFile) {
	std::string directory = configFile["directory_work"];
	ProblemInstance* theProblem = new ProblemInstanceFromFiles(directory+configFile["file_costs"], directory+configFile["file_compat"], directory+configFile["file_cover"], atof(configFile["budget"].c_str()));
	return theProblem;
}

Id2Str* instanceTheNodeName(ConfigurationJaks& configFile) {
	std::string directory = configFile["directory_work"];
	Id2Str* theNodeName = new Id2Str(configFile["directory_work"] + configFile["file_node_name"]);
	return theNodeName;
}

void writeSolution(const SnowFlakeVector& solution, ConfigurationJaks& configFile) {
	if(atoi(configFile["write_file"].c_str())) {
		SnowFlake::writeSolution(solution, configFile["directory_work"] + configFile["name_output"]);
	}
}

void execute(ConfigurationJaks& configFile) {
	int solverId = atoi(configFile["SOLVER"].c_str());
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	bool withSpecificItem = ((configFile["with_specific_item"] == "1") ? true : false);
	int specificItem = atoi(configFile["specific_item"].c_str());
	Solver * theSolver = 0;
	switch(solverId) {
		case ClusterAndPick:
			std::cout<<"Ejecutando ClusterAndPickSolver ..."<<std::endl;
			theSolver = new ClusterAndPickSolver(theProblem);
			break;
		case RestrictedHAC:
			std::cout<<"Ejecutando RestrictedHACSolver ..."<<std::endl;
			theSolver = new RestrictedHACSolver(theProblem);
			break;
		case RestrictedHACSpecific:
			std::cout<<"Ejecutando RestrictedHACSpecificSolver ..."<<std::endl;
			theSolver = new RestrictedHACSWithSpecificItemSolver(theProblem, atoi(configFile["specific_item"].c_str()));
			break;
		case RandomBOBO:
			std::cout<<"Ejecutando RandomBOBOSolver ..."<<std::endl;
			theSolver = new RandomBOBOSolver(theProblem);
			if (withSpecificItem) {
				dynamic_cast<RandomBOBOSolver *> (theSolver)->setSpecificItem(specificItem);
			}
			break;
		case RandomSOBO:
			std::cout<<"Ejecutando RandomSOBOSolver ..."<<std::endl;
			theSolver = new RandomSOBOSolver(theProblem);
			break;
		case ExAnySimSOBO:
			std::cout<<"Ejecutando ExhaustiveGreedyAnySimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedyAnySimSOBOSolver(theProblem);
			break;
		case ExSumSimSOBO:
			std::cout<<"Ejecutando ExhaustiveGreedySumSimSolver ..."<<std::endl;
			theSolver = new ExhaustiveGreedySumSimSOBOSolver(theProblem);
			break;
		case SeqScan:
			std::cout<<"Ejecutando SequentialScanSolver ..."<<std::endl;
			theSolver = new SequentialScanSolver(theProblem);
			break;
		default:
			std::cerr<<"El metodo elegido para la resolucion no existe"<<std::endl;
			break;
	}
	SnowFlakeVector* solution = theSolver->solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solution,theNodeName)<<endl;
	writeSolution(*solution, configFile);
	delete solution;
	delete theProblem;
	delete theSolver;
}
