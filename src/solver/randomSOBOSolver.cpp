/*
 * randomSOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: jknebel
 */

#include "randomSOBOSolver.h"
#include <time.h>
#include <cstdlib>

RandomSOBOSolver::~RandomSOBOSolver() {

}

int RandomSOBOSolver::getPivot(IntSet& pivotsUsed, IntSet& possiblePivots) {
	srand(time(0));
	int pivot = randomNode();
	while(pivotsUsed.count(pivot) != 1 || possiblePivots.count(pivot) == 0) {
		pivot = randomNode();
	}
	return pivot;
}

int RandomSOBOSolver::randomNode() {
	return (rand() % this->problem_->numNodes()) + 1;
}
