//
// Created by zero on 18/08/15.
//

#ifndef TESIS_JAKS_EXE_LOCALSEARCHBUNDLES_H
#define TESIS_JAKS_EXE_LOCALSEARCHBUNDLES_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake>;
using TabuBundles = std::vector<int>;

class LocalSearchBundles {
private:
    void updateTabuElements(std::vector<int> &tabuSet);
    SnowFlake getWorstBundle(SnowFlakeVector &solution, TabuBundles setOfTabuBundles, ProblemInstance &theProblem,
                             Double intersimilarityWeight);

    SnowFlake getCentroidBundle(SnowFlakeVector &solution, ProblemInstance &theProblem, Double interSimilarityWeight);

    SnowFlakeVector getBetterFlakes(SnowFlake centroid, TabuBundles setOfTabuBundles, SnowFlakeVector &remainingFlakes,
                                    ProblemInstance &theProblem, double interSimilarityWeight);
public:
    LocalSearchBundles() {}
    SnowFlakeVector execute(int maxIter, SnowFlakeVector& solution, SnowFlakeVector& remainingFlakes
            , ProblemInstance& theProblem, Double interSimilarityWeight);
};


#endif //TESIS_JAKS_EXE_LOCALSEARCHBUNDLES_H
