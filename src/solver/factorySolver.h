#ifndef FACTORYSOLVER_H
#define FACTORYSOLVER_H

#include "../problem/problemInstance.h"
#include "clusterAndPickSolver.h"
#include "restrictedHACSolver.h"
#include "randomSOBOSolver.h"
#include "randomBOBOSolver.h"
#include "exhaustiveGreedyAnySimSOBOSolver.h"
#include "exhaustiveGreedySumSimSOBOSolver.h"
#include "sequentialScanSolver.h"
#include "restrictedHACWithSpecificItemSolver.h"
#include "greedySolver.h"
#include "../util/configurator/configurationJaks.h"
#include <memory>



class FactorySolver {
private:
    FactorySolver();

public:
    enum SolverAlgorithm {
        ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO,
        RandomSOBO, ExAnySimSOBO, ExSumSimSOBO, SeqScan, LocalSolver
    };

    static std::string getTheSolverName(ConfigurationJaks& configFile);
    static std::unique_ptr<Solver> getTheSolver(ConfigurationJaks& configFile, ProblemInstance* theProblem, Selector *theStrategySelector);
};

#endif // FACTORYSOLVER_H
