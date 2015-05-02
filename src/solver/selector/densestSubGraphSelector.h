#ifndef DENSESTSUBGRAPHSELECTOR_H
#define DENSESTSUBGRAPHSELECTOR_H

#include "selector.h"
#include "../solver.h"

class DensestSubgraphSelector : public Selector {
public:
    DensestSubgraphSelector() : Selector() {}
    SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                   SnowFlakeHelper helper, double interSimilarityWeight, int numRequested);
    ~DensestSubgraphSelector() {}
};

#endif // DENSESTSUBGRAPHSELECTOR_H
