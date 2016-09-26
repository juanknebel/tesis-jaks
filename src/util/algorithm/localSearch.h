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

	int findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem, std::vector<int> &centroidTimes);

	int findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem, std::map<int,int> recentlyAdded);

	std::vector<int> nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
	                                 std::set<int> &allElements, std::set<int> &usedElements,
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
                                    double interSimilarityWeight, int centroid);

    SnowFlakeWithChooseElement
    replaceFarAwayElementInBundle(SnowFlake bundle, int centroidElement, int farAwayElement, std::set<int> &setOfElements,
                                      std::set<int> setOfUsedElements, ProblemInstance &theProblem,
                                      TabuElements setOfTabuElements, bool takeTabu, std::map<int, std::set<int>> mapOfTabus,
                                      int bundleWithWorstInter, SnowFlakeVector iterationSolution, double interSimilarityWeight,
                                      SnowFlakeVector visitedSolution, double theBestObjectiveSolution);

    SnowFlakeWithChooseElement
	removeFarAwayElement(SnowFlake bundle, int farAwayElement, ProblemInstance &theProblem, SnowFlakeVector visitedSolution,
                             double interSimilarityWeight);

public:
	LocalSearch() {}
	SnowFlakeVector execute(int maxIter, const SnowFlakeVector& solution, ProblemInstance& theProblem, double interSimilarityWeight);


};

#endif // LOCALSEARCH_H
