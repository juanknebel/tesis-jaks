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

void executeClusterAndPickSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ClusterAndPickSolver resolverCANP = ClusterAndPickSolver(theProblem);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverCANP.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeRestrictedHACSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RestrictedHACSolver resolverRHAC = RestrictedHACSolver(theProblem);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverRHAC.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeRestrictedHACSpecificSolver(ConfigurationJaks& configFile) {
	
}

void executeRandomBOBOSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RandomBOBOSolver resolverRBOBO = RandomBOBOSolver(theProblem);
	//SnowflakesOneByOneSolver::MAX_TRIALS = atoi(configFile["max_trials"].c_str());
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverRBOBO.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeRandomSOBOSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RandomSOBOSolver resolverRSOBO = RandomSOBOSolver(theProblem);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverRSOBO.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeExhaustiveGreedyAnySimSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ExhaustiveGreedyAnySimSOBOSolver resolverEGAS = ExhaustiveGreedyAnySimSOBOSolver(theProblem);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverEGAS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeExhaustiveGreedySumSimSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ExhaustiveGreedySumSimSOBOSolver resolverEGSS = ExhaustiveGreedySumSimSOBOSolver(theProblem);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SnowFlakeVector* solutions = resolverEGSS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}

void executeSequentialScanSolver ( ConfigurationJaks& configFile ) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	Id2Str* theNodeName = instanceTheNodeName(configFile);
	SequentialScanSolver resolverSS = SequentialScanSolver(theProblem);
	SnowFlakeVector* solutions = resolverSS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions,theNodeName)<<endl;
	delete solutions;
	delete theProblem;
}
