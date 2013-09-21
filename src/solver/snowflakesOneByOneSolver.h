/*
 * snowflakesOneByOneSolver.h
 *
 *  Created on: Aug 12, 2013
 *      Author: amit
 */

#ifndef SNOWFLAKESONEBYONESOLVER_H_
#define SNOWFLAKESONEBYONESOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class SnowflakesOneByOneSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	static bool SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS;

	SnowflakesOneByOneSolver(ProblemInstance* problem) : MultiplicativeEffortProduceAndChooseSolver (problem) {
		this->specificItem = -1;
	}
	~SnowflakesOneByOneSolver() {};

	virtual int getPivot(IntSet& pivotsUsed, IntSet& possiblePivots) = 0;

	void setSpecificItem(int specificItem);

protected:
	SnowFlakeVector* produceManySnowflakes(int numSnowflakes);
	bool candidateAcceptable(SnowFlake& candidate);
	int specificItem;

private:
	SnowFlakeVector* produceManySnowflakesSimple(int numSnowflakes);
	SnowFlakeVector* produceManySnowflakesWithSpecificItem(int numSnowflakes);
};

#endif /* SNOWFLAKESONEBYONESOLVER_H_ */
