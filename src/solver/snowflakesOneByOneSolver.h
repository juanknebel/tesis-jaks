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
	}
	~SnowflakesOneByOneSolver() {};

	virtual int getPivot(IntSet& pivotsUsed, IntSet& possiblePivots) = 0;

protected:
	SnowFlakeVector* produceManySnowflakes(int numSnowflakes);

	virtual bool candidateAcceptable(SnowFlake &candidate);

private:
	SnowFlakeVector* produceManySnowflakesSimple(int numSnowflakes);
    SnowFlakeVector* produceManySnowflakesWithSpecificItem(int numSnowflakes);
};

#endif /* SNOWFLAKESONEBYONESOLVER_H_ */
