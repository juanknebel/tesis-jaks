#include <cstdlib>
#include "util/Logger.h"
#include "executeSolver.h"
#include "problemInstanceFromFiles.h"
#include "solver/clusterAndPickSolver.h"
#include "solver/randomBOBOSolver.h"

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
	
}

void executeExhaustiveGreedyAnySimSolver(ConfigurationJaks& configFile) {
	
}

void executeExhaustiveGreedySumSimSolver(ConfigurationJaks& configFile) {
	
}
