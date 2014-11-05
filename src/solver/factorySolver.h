#ifndef FACTORYSOLVER_H
#define FACTORYSOLVER_H

#include "../problem/problemInstance.h"

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
};

#endif // FACTORYSOLVER_H
