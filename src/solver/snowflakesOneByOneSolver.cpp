/*
 * snowflakesOneByOneSolver.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: amit
 */

#include "snowflakesOneByOneSolver.h"
#include <functional>

bool SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;

SnowFlakeVector* SnowflakesOneByOneSolver::produceManySnowflakes(int numSnowflakes)
{

	if (this->problem_->getSpecificItem() != -1) {
		return this->produceManySnowflakesWithSpecificItem(numSnowflakes);
	}

	else {
		return this->produceManySnowflakesSimple(numSnowflakes);
	}
}

SnowFlakeVector* SnowflakesOneByOneSolver::produceManySnowflakesSimple(int numSnowflakes)
{
	SnowFlakeVector* candidates = new SnowFlakeVector();

	std::set<int> pivotsUsed;
	std::set<int> possiblePivots = std::set<int>(this->problem_->getIds());
	std::set<int> allIds = std::set<int>(this->problem_->getIds());

	int maxTrials = numSnowflakes * 1;

	int trials = 0;

	while((candidates->size() < numSnowflakes) && (possiblePivots.size() > 0) && (trials < maxTrials)) {
		int pivot = this->getPivot(pivotsUsed, possiblePivots);

		//pivot esta en pivotsUsados o pivot no esta en possiblePivots
		if ((pivotsUsed.find(pivot) != pivotsUsed.end()) || (possiblePivots.find(pivot) == possiblePivots.end())) {
			throw Exception(__FILE__, __LINE__, "IllegalStateException Invalid pivot");
		}

		pivotsUsed.insert(pivot);
		possiblePivots.erase(pivot);

		SnowFlake snowflake = this->pickFlake(pivot, allIds);

		if (this->candidateAcceptable(snowflake)) {
			candidates->push_back(snowflake);

			if (!SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS) {
				// Remove all snowflake members from the possible pivots
				for (std::set<int>::iterator id = snowflake.ids().begin(); id != snowflake.ids().end(); ++id) {
					possiblePivots.erase(*id);
				}
			}
		}

		trials++;
	}

	return candidates;

}

SnowFlakeVector* SnowflakesOneByOneSolver::produceManySnowflakesWithSpecificItem(int numSnowflakes)
{
	SnowFlakeVector* candidates = new SnowFlakeVector();

	std::set<int> pivotsUsed;
	std::set<int> possiblePivots = std::set<int>(this->problem_->getIds());
	std::set<int> allIds = std::set<int>(this->problem_->getIds());

	possiblePivots.erase(this->problem_->getSpecificItem());
	allIds.erase(this->problem_->getSpecificItem());

	int maxTrials = numSnowflakes * 1000;

	int trials = 0;

	while((candidates->size() < numSnowflakes) && (possiblePivots.size() > 0) && (trials < maxTrials)) {
		int pivot = this->getPivot(pivotsUsed, possiblePivots);

		if ((pivotsUsed.find(pivot) != pivotsUsed.end()) || (possiblePivots.find(pivot) == possiblePivots.end())) {
			throw Exception(__FILE__, __LINE__, "IllegalStateException Invalid pivot");
		}

		pivotsUsed.insert(pivot);
		possiblePivots.erase(pivot);

		SnowFlake snowflake = this->pickFlake(this->problem_->getSpecificItem(), pivot, allIds);

		if (this->candidateAcceptable(snowflake)) {
			candidates->push_back(snowflake);

			if (!SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS) {
				// Remove all snowflake members from the possible pivots
				for (std::set<int>::iterator id = snowflake.ids().begin(); id != snowflake.ids().end(); ++id) {
					possiblePivots.erase(*id);
				}
			}
		}

		trials++;
	}

	return candidates;
}


bool SnowflakesOneByOneSolver::candidateAcceptable(SnowFlake& candidate)
{
	return true;
}
