#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "produceAndChooseSolver.h"

class LocalSearchSolver : public ProduceAndChooseSolver {
public:
    LocalSearchSolver(ProblemInstance* problem, Selector* selector) : ProduceAndChooseSolver(problem, selector) {
    }
    ~LocalSearchSolver() {}
    SnowFlakeVector* produceManySnowflakes(int numSnowflakes);
    int numToProduce(int numRequested);
};

#endif // LOCALSEARCHSOLVER_H
