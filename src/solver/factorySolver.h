#ifndef FACTORYSOLVER_H
#define FACTORYSOLVER_H

#include "../problem/problemInstance.h"
#include "../solver/clusterAndPickSolver.h"
#include "../solver/restrictedHACSolver.h"
#include "../solver/randomSOBOSolver.h"
#include "../solver/randomBOBOSolver.h"
#include "../solver/exhaustiveGreedyAnySimSOBOSolver.h"
#include "../solver/exhaustiveGreedySumSimSOBOSolver.h"
#include "../solver/sequentialScanSolver.h"
#include "../solver/restrictedHACWithSpecificItemSolver.h"



class FactorySolver {
private:
    Solver* instanceTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
            double interSimilarityWeight, double multiplier);

    ProduceAndChooseSolver::RankingStrategy checkAndReturnStrategy(double similarity, int strategy);
public:
    enum SolverAlgorithm {
        ClusterAndPick, RestrictedHAC, RestrictedHACSpecific, RandomBOBO,
        RandomSOBO, ExAnySimSOBO, ExSumSimSOBO, SeqScan
    };

    FactorySolver();
    std::string getTheSolverName(int solverId);
    Solver* getTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
                         double interSimilarityWeight, double multiplier);

    ProduceAndChooseSolver::RankingStrategy getTheStrategy(int strategy);
};

#endif // FACTORYSOLVER_H
