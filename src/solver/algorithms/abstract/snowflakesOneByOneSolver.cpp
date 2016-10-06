/*
 * snowflakesOneByOneSolver.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: amit
 */

#include "snowflakesOneByOneSolver.h"
#include "../../../problem/factoryFlake.h"

bool SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;

std::vector<SnowFlake> SnowflakesOneByOneSolver::produceManySnowflakes(int numSnowflakes, ProblemInstance &theProblem)
{

	if (theProblem.getSpecificItem() != -1) {
		return this->produceManySnowflakesWithSpecificItem(numSnowflakes, theProblem);
	}

	else {
		return this->produceManySnowflakesSimple(numSnowflakes, theProblem);
	}
}

std::vector<SnowFlake> SnowflakesOneByOneSolver::produceManySnowflakesSimple(int numSnowflakes, ProblemInstance &theProblem)
{
	std::vector<SnowFlake> candidates = std::vector<SnowFlake>();

	std::set<Flake> pivotsUsed;
	std::set<Flake> possiblePivots = FactoryFlake::createAllFlakes(theProblem);
	std::set<Flake> allIds = FactoryFlake::createAllFlakes(theProblem);

	int maxTrials = numSnowflakes * 1;

	int trials = 0;

	while((candidates.size() < numSnowflakes) && (possiblePivots.size() > 0) && (trials < maxTrials)) {
		Flake pivot = this->getPivot(pivotsUsed, possiblePivots, theProblem);

		//pivot esta en pivotsUsados o pivot no esta en possiblePivots
		if ((pivotsUsed.find(pivot) != pivotsUsed.end()) || (possiblePivots.find(pivot) == possiblePivots.end())) {
			throw Exception(__FILE__, __LINE__, "IllegalStateException Invalid pivot");
		}

		pivotsUsed.insert(pivot);
		possiblePivots.erase(pivot);
		SnowFlake snowflake = this->pickFlake(pivot, allIds, theProblem);

		if (this->candidateAcceptable(snowflake, theProblem)) {
			candidates.push_back(snowflake);

			if (!SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS) {
				// Remove all snowflake members from the possible pivots
				for (auto aFlake : snowflake.ids()) {
					possiblePivots.erase(aFlake);
				}
			}
		}

		trials++;
	}

	return candidates;

}

std::vector<SnowFlake>
SnowflakesOneByOneSolver::produceManySnowflakesWithSpecificItem(int numSnowflakes, ProblemInstance &theProblem)
{
	std::vector<SnowFlake> candidates = std::vector<SnowFlake>();

	std::set<Flake> pivotsUsed;
	std::set<Flake> possiblePivots = FactoryFlake::createAllFlakes(theProblem);
	std::set<Flake> allIds = FactoryFlake::createAllFlakes(theProblem);

	possiblePivots.erase(this->specificItem_);
	allIds.erase(this->specificItem_);

	int maxTrials = numSnowflakes * 1000;

	int trials = 0;

	while((candidates.size() < numSnowflakes) && (possiblePivots.size() > 0) && (trials < maxTrials)) {
		Flake pivot = this->getPivot(pivotsUsed, possiblePivots, theProblem);

		if ((pivotsUsed.find(pivot) != pivotsUsed.end()) || (possiblePivots.find(pivot) == possiblePivots.end())) {
			throw Exception(__FILE__, __LINE__, "IllegalStateException Invalid pivot");
		}

		pivotsUsed.insert(pivot);
		possiblePivots.erase(pivot);

		SnowFlake snowflake = this->pickFlake(this->specificItem_, pivot, allIds, theProblem);

		if (this->candidateAcceptable(snowflake, theProblem)) {
			candidates.push_back(snowflake);

			if (!SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS) {
				// Remove all snowflake members from the possible pivots
				for (auto aFlake : snowflake.ids()) {
					possiblePivots.erase(aFlake);
				}
			}
		}

		trials++;
	}

	return candidates;
}


bool SnowflakesOneByOneSolver::candidateAcceptable(SnowFlake& candidate, ProblemInstance &theProblem)
{
	return true;
}
