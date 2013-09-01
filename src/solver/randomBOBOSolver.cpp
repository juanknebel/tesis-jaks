/*
 * randomBOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#include <algorithm>
#include "randomBOBOSolver.h"

int RandomBOBOSolver::INITIAL_TRIALS_FOR_MU = 5;

RandomBOBOSolver::~RandomBOBOSolver() {

}

Double RandomBOBOSolver::chooseMu() {
	DblVector listOfSumIntra = DblVector(this->INITIAL_TRIALS_FOR_MU);
	IntSet allIds = IntSet(this->problem_->getIds());
	int pivot;
	Double median = 0.0;

	for (Uint i = 0; i < this->INITIAL_TRIALS_FOR_MU; ++i) {
		pivot = this->randomNode();
		listOfSumIntra.push_back(this->pickFlake(pivot, allIds)->getSumIntraCompat());
	}
	sort(listOfSumIntra.begin(), listOfSumIntra.end());
	int middle = listOfSumIntra[this->INITIAL_TRIALS_FOR_MU/2];

	if (this->INITIAL_TRIALS_FOR_MU % 2 == 0) {
		median = (listOfSumIntra[middle] + listOfSumIntra[middle - 1])/2;
	}
	else {
		median = listOfSumIntra[middle];
	}

	return median;
}

bool RandomBOBOSolver::candidateAcceptable(SnowFlake& candidate) {
	return candidate.getSumIntraCompat() >= this->mu_;
}
