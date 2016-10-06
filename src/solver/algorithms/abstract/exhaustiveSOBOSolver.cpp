/*
 * exaustiveSOBOSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "exhaustiveSOBOSolver.h"

Flake ExhaustiveSOBOSolver::getPivot(std::set<Flake> &pivotsUsed, std::set<Flake> &possiblePivots, ProblemInstance& theProblem)
{
	Flake minPivot = Flake();

	for (auto possiblePivot : possiblePivots) {
		if (pivotsUsed.find(possiblePivot)==pivotsUsed.end()) {
			if (possiblePivot.getId() < minPivot.getId()) {
				minPivot = possiblePivot;
			}
		}
	}

	if (minPivot == Flake()) {
		throw Exception(__FILE__, __LINE__, "IllegalStateException Could not get a valid pivot");
	}

	return minPivot;
}

int ExhaustiveSOBOSolver::numToProduce(int requestedSnowflakes)
{
	/*
	 * TODO: revisar esto
	 */
	return 1000;
}

