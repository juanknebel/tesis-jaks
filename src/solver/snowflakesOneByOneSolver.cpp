/*
 * snowflakesOneByOneSolver.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: amit
 */

#include "snowflakesOneByOneSolver.h"

bool SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;

SnowflakesOneByOneSolver::~SnowflakesOneByOneSolver() {
	// TODO Auto-generated destructor stub
}

SnowFlakeVector* SnowflakesOneByOneSolver::produceManySnowflakes(int numSnowflakes){

	SnowFlakeVector* candidates;
	candidates = new SnowFlakeVector(numSnowflakes);

	IntSet pivotsUsed = IntSet();
	IntSet possiblePivots = IntSet(this->problem_->getIds());
	IntSet allIds = IntSet(this->problem_->getIds());

	int maxTrials = numSnowflakes * 1000;

	int trials = 0;

	while((candidates->size() < 0) && (possiblePivots.size() > 0) && (trials < maxTrials)){
		int pivot = this->getPivot(pivotsUsed, possiblePivots);
		if ((pivotsUsed.find(pivot) != pivotsUsed.end()) || (possiblePivots.find(pivot) != possiblePivots.end())) {
			//throw
		}

		pivotsUsed.insert(pivot);
		possiblePivots.erase(pivot);

		SnowFlake* snowflake = this->pickFlake(pivot, allIds);
		if (this->candidateAcceptable(*snowflake)) {
			candidates->push_back(*snowflake);
			if (!SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS) {
				// Remove all snowflake members from the possible pivots
				for (IntSet::iterator id = snowflake->ids().begin(); id != snowflake->ids().end(); ++id) {
					possiblePivots.erase(*id);
				}
			}
		}

		trials++;
		delete snowflake;
	}
	return candidates;
}

bool SnowflakesOneByOneSolver::candidateAcceptable(SnowFlake& candidate){
	return true;
}
