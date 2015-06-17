#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake>;

class LocalSearch {
private:
    struct UsedElements {
        int snowFlakeId;
        int countBetter;
        int countTabu;
    };

public:
    LocalSearch() {}
    SnowFlakeVector execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight);

    int findWorstIntraBundle(SnowFlakeVector &vector);

    int findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem);

    int findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem);

    std::vector<int> nearestElements(int centroid, SnowFlake worstFlake, IntSet &allElements,
                                     std::set &usedElements, ProblemInstance &theProblem);

    SnowFlake createNewBunlde(SnowFlake worstFlake, int anElement);

    bool checkCoverageConstraint(SnowFlake worstFlake, int centroid, const int newElement, ProblemInstance &theProblem);
};

#endif // LOCALSEARCH_H
