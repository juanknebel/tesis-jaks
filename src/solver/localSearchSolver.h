#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "solver.h"

class LocalSearchSolver : public Solver {
public:
    LocalSearchSolver(ProblemInstance* problem) : Solver(problem) {

    }
    void setInterSimilarityWeight(Double interSimilarityWeight);
    ~LocalSearchSolver() {}
    SnowFlakeVector* solve(int numSnowFlakes);
};

#endif // LOCALSEARCHSOLVER_H
