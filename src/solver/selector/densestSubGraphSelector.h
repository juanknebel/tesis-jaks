#ifndef DENSESTSUBGRAPHSELECTOR_H
#define DENSESTSUBGRAPHSELECTOR_H

#include "selector.h"
#include "../solver.h"

class DensestSubgraphSelector : public Selector {
public:
    DensestSubgraphSelector(double interSimilarityWeight, ProblemInstance* theProblem) : Selector(interSimilarityWeight, theProblem) {}
    SnowFlakeVector *getTopSolution(SnowFlakeVector *produced, int numRequested);
    ~DensestSubgraphSelector();
};

#endif // DENSESTSUBGRAPHSELECTOR_H
