#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake>;
using TabuElements = std::map<int, int>;
using TabuBundles = std::vector<int>;

class LocalSearch {
private:
    int findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles);

    int findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem);

    int findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem);

    std::vector<int> nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
                                                  IntSet &allElements, std::set<int> &usedElements,
                                                  ProblemInstance &theProblem, TabuElements &tabuElements);

    SnowFlake createNewBunlde(SnowFlake worstFlake, int excludeElement, int newElement,
                              ProblemInstance &theProblem);

    bool checkCoverageConstraint(SnowFlake worstFlake, int elementToReplace, int newElement,
                                 ProblemInstance &theProblem);

public:
    LocalSearch() {}
    SnowFlakeVector execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight);

    void updateTabuElements(TabuElements &tabuSet);
    void updateTabuElements(TabuBundles &tabuSet);
};

#endif // LOCALSEARCH_H
