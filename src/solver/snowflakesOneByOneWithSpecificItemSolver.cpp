/*
 * snowflakesOneByOneWithSpecificItemSolver.cpp
 *
 *  Created on: Aug 29, 2013
 *      Author: amit
 */

#include "snowflakesOneByOneWithSpecificItemSolver.h"

snowflakesOneByOneWithSpecificItemSolver::~snowflakesOneByOneWithSpecificItemSolver() {
}

SnowFlakeVector* snowflakesOneByOneWithSpecificItemSolver::produceManySnowflakes(int numSnowflakes){

	SnowFlakeVector* candidates;
	candidates = new SnowFlakeVector();

	IntSet allIds = IntSet(this->problem_->getIds());
	allIds.erase(this->_specificItem);

	int maxTrials = numSnowflakes * 1000;

	int trials = 0;

	while((candidates->size() < numSnowflakes) && (trials < maxTrials)){
		int pivot = this->_specificItem;

		SnowFlake* snowflake = this->pickFlake(pivot, allIds);
		if (this->candidateAcceptable(*snowflake)) {
			candidates->push_back(*snowflake);
			IntSet snowflakeIds = snowflake->ids();
			allIds.erase(snowflakeIds.begin(),snowflakeIds.end());
		}

		trials++;
	}
	return candidates;
}

bool snowflakesOneByOneWithSpecificItemSolver::candidateAcceptable(SnowFlake& candidate){
	return true;
}
