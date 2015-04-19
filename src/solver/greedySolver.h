#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "produceAndChooseSolver.h"

class GreedySolver : public ProduceAndChooseSolver {
public:
    GreedySolver(ProblemInstance* problem, Selector* selector) : ProduceAndChooseSolver(problem, selector) {
    }
    ~GreedySolver() {}
    SnowFlakeVector* produceManySnowflakes(int numSnowflakes);
    int numToProduce(int numRequested);
};

#endif // LOCALSEARCHSOLVER_H
