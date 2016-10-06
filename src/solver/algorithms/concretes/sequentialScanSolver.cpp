/*
 * sequentialScanSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "sequentialScanSolver.h"
#include "../../../problem/factoryFlake.h"

std::vector<SnowFlake> SequentialScanSolver::solve(ProblemInstance& theProblem, int numSnowFlakes)
{
	std::vector<SnowFlake> solution = std::vector<SnowFlake>();
	std::set<Flake> nodes = FactoryFlake::createAllFlakes(theProblem);
	std::set<Flake> currentSnowflake = std::set<Flake>();

	while(!nodes.empty()) {
		bool added = false;
		for (auto aFlake : nodes) {
			if (this->checkBudgetAndCoverageConstraint(currentSnowflake, aFlake, theProblem)) {
				currentSnowflake.insert(aFlake);
				nodes.erase(aFlake);
				added = true;
				break;
			}
		}

		if (!added) {
			solution.push_back(SnowFlake(currentSnowflake));
			currentSnowflake.clear();

			if (solution.size() == numSnowFlakes) {
				return solution;
			}
		}
	}

	if ((solution.size() < numSnowFlakes) && (!currentSnowflake.empty())) {
		solution.push_back(SnowFlake(currentSnowflake));
	}

	return solution;
}

Flake SequentialScanSolver::pickRandom(const std::set<Flake>& set)
{
	std::vector<Flake> elements;
	std::copy(set.begin(), set.end(), std::back_inserter(elements));
	int position = (rand() % elements.size());

	return elements[position];
}

