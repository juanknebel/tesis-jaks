/*
 * exaustiveSOBOSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "exhaustiveSOBOSolver.h"
#include <limits>

int ExhaustiveSOBOSolver::getPivot(std::set<int>& pivotsUsed, std::set<int>& possiblePivots){
	int minPivot = std::numeric_limits<int>::max();

	for (std::set<int>::iterator possiblePivot = possiblePivots.begin(); possiblePivot != possiblePivots.end(); ++possiblePivot) {
		if (pivotsUsed.find(*possiblePivot)==pivotsUsed.end()) {
			if (*possiblePivot < minPivot) {
				minPivot = *possiblePivot;
			}
		}
	}

	if (minPivot == std::numeric_limits<int>::max()) {
		throw Exception(__FILE__, __LINE__, "IllegalStateException Could not get a valid pivot");
	}

	return minPivot;
}

int ExhaustiveSOBOSolver::numToProduce(int requestedSnowflakes){
	return this->problem_->numNodes();
}

