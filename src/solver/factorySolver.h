//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYSOLVER_H
#define TESIS_JAKS_EXE_FACTORYSOLVER_H
#include <memory>
#include "algorithms/concretes/clusterAndPickSolver.h"
#include "algorithms/concretes/restrictedHACSolver.h"
#include "algorithms/concretes/restrictedEfficientHACSolver.h"
#include "algorithms/concretes/randomSOBOSolver.h"
#include "algorithms/concretes/randomBOBOSolver.h"
#include "algorithms/concretes/exhaustiveGreedyAnySimSOBOSolver.h"
#include "algorithms/concretes/exhaustiveGreedySumSimSOBOSolver.h"
#include "algorithms/concretes/sequentialScanSolver.h"
#include "algorithms/concretes/restrictedHACWithSpecificItemSolver.h"
#include "algorithms/concretes/greedySolver.h"

class FactorySolver {
public:
    enum SolverAlgorithmNew {
        EfficientHAC, RestrictedHAC, RandomBOBO, AllGreedySolver, ExSumSimSOBO, ExAnySimSOBO,
        RandomSOBO, SeqScan, ClusterAndPick, RestrictedHACSpecific
    };

    static unique_ptr<Solver>
    getTheSolver(std::string algorithm, std::string strategy, int multiplier, double gamma, double budget);

private:
    FactorySolver();
    static FactorySolver::SolverAlgorithmNew getSolverByName(std::string algorithm);
    static ProduceAndChooseSolver::RankingStrategy getStrategyByName(std::string strategy);
};


#endif //TESIS_JAKS_EXE_FACTORYSOLVER_H
