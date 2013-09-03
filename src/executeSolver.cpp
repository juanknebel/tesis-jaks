#include <cstdlib>
#include "util/Logger.h"
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

void executeClusterAndPickSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ClusterAndPickSolver resolverCANP = ClusterAndPickSolver(theProblem);
	SnowFlakeVector* solutions = resolverCANP.solve(atoi(configFile["num_flakes"].c_str()));
}

void executeRestrictedHACSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RestrictedHACSolver resolverRHAC = RestrictedHACSolver(theProblem);
	SnowFlakeVector* solutions = resolverRHAC.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}

void executeRestrictedHACSpecificSolver(ConfigurationJaks& configFile) {
	
}

void executeRandomBOBOSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RandomBOBOSolver resolverRBOBO = RandomBOBOSolver(theProblem);
	SnowFlakeVector* solutions = resolverRBOBO.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}

void executeRandomSOBOSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	RandomSOBOSolver resolverRSOBO = RandomSOBOSolver(theProblem);
	SnowFlakeVector* solutions = resolverRSOBO.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}

void executeExhaustiveGreedyAnySimSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ExhaustiveGreedyAnySimSOBOSolver resolverEGAS = ExhaustiveGreedyAnySimSOBOSolver(theProblem);
	SnowFlakeVector* solutions = resolverEGAS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}

void executeExhaustiveGreedySumSimSolver(ConfigurationJaks& configFile) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	ExhaustiveGreedySumSimSOBOSolver resolverEGSS = ExhaustiveGreedySumSimSOBOSolver(theProblem);
	SnowFlakeVector* solutions = resolverEGSS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}

void executeSequentialScanSolver ( ConfigurationJaks& configFile ) {
	ProblemInstance *theProblem = instanceTheProblem(configFile);
	SequentialScanSolver resolverSS = SequentialScanSolver(theProblem);
	SnowFlakeVector* solutions = resolverSS.solve(atoi(configFile["num_flakes"].c_str()));
	cout<<SnowFlake::showSolution(*solutions)<<endl;
}
