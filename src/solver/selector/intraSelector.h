#ifndef INTRASELECTOR_H
#define INTRASELECTOR_H

#include "selector.h"

class IntraSelector : public Selector {
public:
    IntraSelector(double interSimilarityWeight, ProblemInstance* theProblem) : Selector(interSimilarityWeight, theProblem) {}
    SnowFlakeVector* getTopSolution(SnowFlakeVector* produced, int numRequested);
    ~IntraSelector();
};

#endif // INTRASELECTOR_H
