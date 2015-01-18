/*
 * produceAndChooseSolver.cpp
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#include "produceAndChooseSolver.h"
#include "../util/system/stringUtilities.h"
#include "selector/intraSelector.h"
#include <float.h>

Selector* ProduceAndChooseSolver::getSelector() {
    return this->theSelectorStrategy_;
}

void ProduceAndChooseSolver::setInterSimilarityWeight(double interSimilarityWeight) {
		this->interSimilarityWeight_ = interSimilarityWeight;
}

SnowFlakeVector* ProduceAndChooseSolver::solve(int numSnowFlakes) {
	SnowFlakeVector* produced = this->produceManySnowflakes(this->numToProduce(numSnowFlakes));
    DEBUG(DBG_DEBUG, "Cantidad de cluser "<<produced->size())
	produced = this->getTopSolutionByRankingStrategy(produced, numSnowFlakes);
	return produced;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionByRankingStrategy(SnowFlakeVector* produced, int numRequested ) {
	SnowFlakeVector* ret;
    ret = this->theSelectorStrategy_->getTopSolution(produced, numRequested);
	produced->clear();
	delete produced;
	return ret;
}

Selector* ProduceAndChooseSolver::getDefault() {
    return nullptr;
}
