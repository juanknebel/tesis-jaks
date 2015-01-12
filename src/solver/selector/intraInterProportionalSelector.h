#ifndef INTRAINTERPROPORTIONALSELECTOR_H
#define INTRAINTERPROPORTIONALSELECTOR_H

#include "selector.h"
#include "../solver.h"

class IntraInterProportionalSelector : public Selector {
public:
    IntraInterProportionalSelector(Double interSimilarityWeight, ProblemInstance* theProblem) : Selector(interSimilarityWeight, theProblem) {}
    SnowFlakeVector *getTopSolution(SnowFlakeVector *produced, int numRequested);
    ~IntraInterProportionalSelector();
};

#endif // INTRAINTERPROPORTIONALSELECTOR_H
