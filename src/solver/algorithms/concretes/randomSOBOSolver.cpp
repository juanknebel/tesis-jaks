/*
 * randomSOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: jknebel
 */

#include "randomSOBOSolver.h"
#include "../../../problem/factoryFlake.h"

Flake RandomSOBOSolver::getPivot(std::set<Flake>& pivotsUsed, std::set<Flake>& possiblePivots, ProblemInstance& theProblem)
{
	Flake pivot = randomNode(theProblem);

	while (pivotsUsed.count(pivot) == 1 || possiblePivots.count(pivot) != 1) {
		pivot = randomNode(theProblem);
	}

	return pivot;
}

Flake RandomSOBOSolver::randomNode(ProblemInstance& theProblem)
{
	return FactoryFlake::createNewFlake(rand() % theProblem.numNodes(), theProblem);
}
