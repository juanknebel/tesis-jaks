//
// Created by zero on 11/09/16.
//

#ifndef TESIS_JAKS_EXE_FACTORYSOLVER_H
#define TESIS_JAKS_EXE_FACTORYSOLVER_H
#include <memory>
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

class FactorySolver {
private:
    FactorySolver();

public:
    enum SolverAlgorithm {
        EfficientHAC, RestrictedHAC, RandomBOBO, AllGreedySolver, ExSumSimSOBO, ExAnySimSOBO,
        RandomSOBO, SeqScan, ClusterAndPick, RestrictedHACSpecific
    };
    static std::unique_ptr<Solver> getTheSolver(ProblemInstance* theProblem, std::string algorithm, std::string strategy, int multiplier, double gamma);
};


#endif //TESIS_JAKS_EXE_FACTORYSOLVER_H
