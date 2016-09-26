/*
 * randomSOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: jknebel
 */

#include "randomSOBOSolver.h"

int RandomSOBOSolver::getPivot(std::set<int>& pivotsUsed, std::set<int>& possiblePivots)
{
	int pivot = randomNode();

	while (pivotsUsed.count(pivot) == 1 || possiblePivots.count(pivot) != 1) {
		pivot = randomNode();
	}

	return pivot;
}

int RandomSOBOSolver::randomNode()
{
	return (rand() % this->problem_->numNodes());
}
