#ifndef FACTORYSOLVER_H
#define FACTORYSOLVER_H

#include "../problem/problemInstance.h"
#include "clusterAndPickSolver.h"
#include "restrictedHACSolver.h"
#include "restrictedEfficientHACSolver.h"
#include "randomSOBOSolver.h"
#include "randomBOBOSolver.h"
#include "exhaustiveGreedyAnySimSOBOSolver.h"
#include "exhaustiveGreedySumSimSOBOSolver.h"
#include "sequentialScanSolver.h"
#include "restrictedHACWithSpecificItemSolver.h"
#include "greedySolver.h"
#include "../util/configurator/configurationJaks.h"



class FactorySolverOLD {
private:
	FactorySolverOLD();

public:
	enum SolverAlgorithm {
	    EfficientHAC, RestrictedHAC, RandomBOBO, AllGreedySolver, ExSumSimSOBO, ExAnySimSOBO,
	    RandomSOBO, SeqScan, ClusterAndPick, RestrictedHACSpecific
	};

	static std::string getTheSolverName(ConfigurationJaks& configFile);
	static Solver* getTheSolver(ConfigurationJaks& configFile, ProblemInstance* theProblem);
	static ProduceAndChooseSolver::RankingStrategy getTheStrategy(ConfigurationJaks& configFile);
};

#endif // FACTORYSOLVER_H
