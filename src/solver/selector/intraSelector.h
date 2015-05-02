#ifndef INTRASELECTOR_H
#define INTRASELECTOR_H

#include "selector.h"

class IntraSelector : public Selector {
public:
    IntraSelector() : Selector() {}
    SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                   SnowFlakeHelper helper, double interSimilarityWeight, int numRequested);
    ~IntraSelector() {}
};

#endif // INTRASELECTOR_H
