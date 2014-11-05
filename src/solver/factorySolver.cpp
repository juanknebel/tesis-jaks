#include "factorySolver.h"
#include "clusterAndPickSolver.h"
#include "restrictedHACSolver.h"
#include "randomSOBOSolver.h"
#include "randomBOBOSolver.h"
#include "exhaustiveGreedyAnySimSOBOSolver.h"
#include "exhaustiveGreedySumSimSOBOSolver.h"
#include "sequentialScanSolver.h"
#include "restrictedHACWithSpecificItemSolver.h"

FactorySolver::FactorySolver() {
}

Solver* FactorySolver::instanceTheSolver(int solverId, ProblemInstance* theProblem, int strategyId,
                                         double interSimilarityWeight, double multiplier) {
    ProduceAndChooseSolver::RankingStrategy theStrategy = this->checkAndReturnStrategy(similarity, strategy);

}
