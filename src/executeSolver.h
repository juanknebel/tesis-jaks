#include "util/configurationJaks.h"

enum SolverAlgorithm {
	ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO, RandomSOBO, ExAnySimSOBO, ExSumSimSOBO
};

void executeClusterAndPickSolver(ConfigurationJaks& configFile);
void executeRestrictedHACSolver(ConfigurationJaks& configFile);
void executeRestrictedHACSpecificSolver(ConfigurationJaks& configFile);
void executeRandomBOBOSolver(ConfigurationJaks& configFile);
void executeRandomSOBOSolver(ConfigurationJaks& configFile);
void executeExhaustiveGreedyAnySimSolver(ConfigurationJaks& configFile);
void executeExhaustiveGreedySumSimSolver(ConfigurationJaks& configFile);
