/*
 * randomBOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#include <algorithm>
#include "randomBOBOSolver.h"
#include "../../../problem/factoryFlake.h"

int RandomBOBOSolver::INITIAL_TRIALS_FOR_MU = 5;

void RandomBOBOSolver::chooseMu(ProblemInstance &theProblem)
{
	/*
	 * TODO: esto se puede mejorar
	 */
	if (this->mu_ == -1.00) {
		std::vector<double> listOfSumIntra = std::vector<double>((unsigned long) this->INITIAL_TRIALS_FOR_MU);
		std::set<Flake> allIds = FactoryFlake::createAllFlakes(theProblem);
		Flake pivot;
		double median = 0.0;

		for (int i = 0; i < this->INITIAL_TRIALS_FOR_MU; ++i) {
			pivot = this->randomNode(theProblem);
			SnowFlake aSnow = this->pickFlake(pivot, allIds, theProblem);
			listOfSumIntra.push_back(SnowFlake::getSumIntraCompat(aSnow, theProblem));
		}

		std::sort(listOfSumIntra.begin(), listOfSumIntra.end());
		int middle = (int) listOfSumIntra[this->INITIAL_TRIALS_FOR_MU / 2];

		if (this->INITIAL_TRIALS_FOR_MU % 2 == 0) {
			median = (listOfSumIntra[middle] + listOfSumIntra[middle - 1]) / 2;
		} else {
			median = listOfSumIntra[middle];
		}

		this->mu_ = median;
	}
}

bool RandomBOBOSolver::candidateAcceptable(SnowFlake& candidate, ProblemInstance &theProblem)
{
	this->chooseMu(theProblem);
	return SnowFlake::getSumIntraCompat(candidate, theProblem) >= this->mu_;
}
