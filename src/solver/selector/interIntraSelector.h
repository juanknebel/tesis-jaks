#ifndef INTERINTRASELECTOR_H
#define INTERINTRASELECTOR_H

#include "selector.h"
#include "../solver.h"

class InterIntraSelector : public Selector {
public:
    InterIntraSelector() : Selector() {}
    SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                   SnowFlakeHelper helper, double interSimilarityWeight, int numRequested);
    ~InterIntraSelector() {}
};

#endif // INTERINTRASELECTOR_H
