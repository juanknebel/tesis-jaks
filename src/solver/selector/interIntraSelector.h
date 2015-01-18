#ifndef INTERINTRASELECTOR_H
#define INTERINTRASELECTOR_H

#include "selector.h"
#include "../solver.h"

class InterIntraSelector : public Selector {
public:
    InterIntraSelector(double interSimilarityWeight, ProblemInstance* theProblem) : Selector(interSimilarityWeight, theProblem) {}
    SnowFlakeVector *getTopSolution(SnowFlakeVector *produced, int numRequested);
    ~InterIntraSelector();
};

#endif // INTERINTRASELECTOR_H
