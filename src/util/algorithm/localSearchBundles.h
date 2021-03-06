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
	                         double intersimilarityWeight);

	SnowFlake getCentroidBundle(SnowFlake worstBundle, SnowFlakeVector &solution,
	                            ProblemInstance &theProblem, double interSimilarityWeight);

	SnowFlakeVector getBetterFlakes(SnowFlake centroid, TabuBundles setOfTabuBundles,
	                                SnowFlakeVector &remainingFlakes, ProblemInstance &theProblem, bool takeTabu);
public:
	LocalSearchBundles() {}
	SnowFlakeVector execute(int maxIter, SnowFlakeVector& solution, SnowFlakeVector& remainingFlakes
	                        , ProblemInstance& theProblem, double interSimilarityWeight);
};


#endif //TESIS_JAKS_EXE_LOCALSEARCHBUNDLES_H
