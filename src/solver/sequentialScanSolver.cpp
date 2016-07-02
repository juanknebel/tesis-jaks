/*
 * sequentialScanSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "sequentialScanSolver.h"
#include <cstdlib>

SnowFlakeVector* SequentialScanSolver::solve(int numSnowflakes)
{
	SnowFlakeVector* solution = new SnowFlakeVector;
	IntSet nodes = IntSet(this->problem_->getIds());
	IntSet currentSnowflake = IntSet();

	while(!nodes.empty()) {
		bool added = false;

		for (IntSet::iterator node = nodes.begin(); node != nodes.end(); ++node) {
			if (this->checkBudgetAndCoverageConstraint(currentSnowflake, *node)) {
				currentSnowflake.insert(*node);
				nodes.erase(*node);
				added = true;
				break;
			}
		}

		if (!added) {
			solution->push_back(SnowFlake(IntSet(currentSnowflake), this->problem_));
			currentSnowflake.clear();

			if (solution->size() == numSnowflakes) {
				return solution;
			}
		}
	}

	if ((solution->size() < numSnowflakes) && (!currentSnowflake.empty())) {
		solution->push_back(SnowFlake(IntSet(currentSnowflake), this->problem_));
	}

	return solution;
}

int SequentialScanSolver::pickRandom(const IntSet& set)
{
	IntVector elements;
	std::copy(set.begin(), set.end(), std::back_inserter(elements));
	int position = (rand() % elements.size());

	return elements[position];
}

