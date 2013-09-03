/*
 * multiplicativeEffortProduceAndChooseSolver.cpp
 *
 *  Created on: 10/08/2013
 *      Author: zero
 */

#include "multiplicativeEffortProduceAndChooseSolver.h"
#include <algorithm>

Double MultiplicativeEffortProduceAndChooseSolver::DEFAULT_NUMCANDIDATES_MULTIPLIER = 2.0;

void MultiplicativeEffortProduceAndChooseSolver::setNumCandidatesMultiplier(Double numCandidatesMultiplier) {
	this->numCandidatesMultiplier_ = numCandidatesMultiplier;
}

int MultiplicativeEffortProduceAndChooseSolver::numToProduce(int requestedSnowFlake) {
	return std::min((int) (requestedSnowFlake * this->numCandidatesMultiplier_), this->problem_->numNodes());
}
