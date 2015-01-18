#ifndef INTERINTRATUPLESSELECTOR_H
#define INTERINTRATUPLES_H

#include "selector.h"
#include "../solver.h"

class InterIntraTuplesSelector : public Selector {
public:
    InterIntraTuplesSelector(double interSimilarityWeight, ProblemInstance* theProblem) : Selector(interSimilarityWeight, theProblem) {}
    SnowFlakeVector *getTopSolution(SnowFlakeVector *produced, int numRequested);
    ~InterIntraTuplesSelector();
};

#endif // INTERINTRATUPLESSELECTOR_H
