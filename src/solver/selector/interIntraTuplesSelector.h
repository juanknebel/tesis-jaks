#ifndef INTERINTRATUPLESSELECTOR_H
#define INTERINTRATUPLES_H

#include "selector.h"
#include "../solver.h"

class InterIntraTuplesSelector : public Selector {
public:
    InterIntraTuplesSelector() : Selector() {}
    SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                   SnowFlakeHelper helper, double interSimilarityWeight, int numRequested);
    ~InterIntraTuplesSelector() {}
};

#endif // INTERINTRATUPLESSELECTOR_H
