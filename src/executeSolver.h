#include "util/configurationJaks.h"

enum SolverAlgorithm {
	ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO, RandomSOBO, ExAnySimSOBO, ExSumSimSOBO, SeqScan
};

void execute(ConfigurationJaks& configFileName);
