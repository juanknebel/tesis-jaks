/*
 * randomBOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#include <algorithm>
#include "randomBOBOSolver.h"

int RandomBOBOSolver::INITIAL_TRIALS_FOR_MU = 5;

double RandomBOBOSolver::chooseMu() {
    std::vector<double> listOfSumIntra = std::vector<double>(this->INITIAL_TRIALS_FOR_MU);
	std::set<int> allIds = std::set<int>(this->problem_->getIds());
	int pivot;
	double median = 0.0;

	for (unsigned int i = 0; i < this->INITIAL_TRIALS_FOR_MU; ++i) {
		pivot = this->randomNode();
		listOfSumIntra.push_back(this->pickFlake(pivot, allIds)->getSumIntraCompat());
	}
	std::sort(listOfSumIntra.begin(), listOfSumIntra.end());
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
