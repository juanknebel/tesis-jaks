#ifndef INTRAINTERPROPORTIONALSELECTOR_H
#define INTRAINTERPROPORTIONALSELECTOR_H

#include "selector.h"
#include "../solver.h"

class IntraInterProportionalSelector : public Selector {
public:
    IntraInterProportionalSelector() : Selector() {}
    SnowFlakeVector getTopSolution(SnowFlakeVector &produced, ProblemInstance &theProblem,
                                   SnowFlakeHelper helper, double interSimilarityWeight, int numRequested);
    ~IntraInterProportionalSelector() {}
};

#endif // INTRAINTERPROPORTIONALSELECTOR_H
