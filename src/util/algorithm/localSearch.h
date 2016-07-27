#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "../../problem/snowFlake.h"
#include <memory>

using SnowFlakeVector = std::vector<SnowFlake>;
using TabuElements = std::vector<int>;
using TabuBundles = std::vector<int>;

class LocalSearch {
private:
	int findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles, bool takeTabu);

	int findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem);

	int findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem, std::map<int,int> recentlyAdded);

	std::vector<int> nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
	                                 IntSet &allElements, std::set<int> &usedElements,
	                                 ProblemInstance &theProblem, std::vector<int> &tabuElements, bool takeTabu, std::map<int, std::set<int>> mapOfTabus);

	SnowFlake createNewBunlde(SnowFlake worstFlake, int excludeElement, int newElement,
	                          ProblemInstance &theProblem);

	bool checkCoverageConstraint(SnowFlake worstFlake, int elementToReplace, int newElement,
	                             ProblemInstance &theProblem);

	void updateTabuElements(std::vector<int> &tabuSet);

    struct SnowFlakeWithChooseElement {
        SnowFlake theSnowflake;
        int theIdOfTheChoosenElement;
		double objetiveFunction;
		bool operator < (const SnowFlakeWithChooseElement& s1) const {
			return this->objetiveFunction < s1.objetiveFunction;
		}
    };

    SnowFlakeWithChooseElement
    addOneRandomElementToBundle(SnowFlake bundle, ProblemInstance &theProblem, std::set<int> setOfUsedElements,
                                    TabuElements setOfTabuBundles, SnowFlakeVector visitedSolution,
                                    Double interSimilarityWeight, int centroid);

    SnowFlakeWithChooseElement
    replaceFarAwayElementInBundle(SnowFlake bundle, int centroidElement, int farAwayElement, IntSet &setOfElements,
                                      std::set<int> setOfUsedElements, ProblemInstance &theProblem,
                                      TabuElements setOfTabuElements, bool takeTabu, std::map<int, std::set<int>> mapOfTabus,
                                      int bundleWithWorstInter, SnowFlakeVector iterationSolution, Double interSimilarityWeight,
                                      SnowFlakeVector visitedSolution, double theBestObjectiveSolution);

    SnowFlakeWithChooseElement
	removeFarAwayElement(SnowFlake bundle, int farAwayElement, ProblemInstance &theProblem, SnowFlakeVector visitedSolution,
                             Double interSimilarityWeight);

public:
	LocalSearch() {}
	SnowFlakeVector execute(int maxIter, const SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight);


};

#endif // LOCALSEARCH_H
