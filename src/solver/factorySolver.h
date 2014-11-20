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
#include "localSearchSolver.h"



class FactorySolver {
private:
    Solver* instanceTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
            double interSimilarityWeight, double multiplier);

    ProduceAndChooseSolver::RankingStrategy checkAndReturnStrategy(double similarity, int strategy);
public:
    enum SolverAlgorithm {
        ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO,
        RandomSOBO, ExAnySimSOBO, ExSumSimSOBO, SeqScan, LocalSolver
    };

    FactorySolver();
    std::string getTheSolverName(int solverId);
    Solver* getTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
                         double interSimilarityWeight, double multiplier);

    ProduceAndChooseSolver::RankingStrategy getTheStrategy(int strategy);
};

#endif // FACTORYSOLVER_H
