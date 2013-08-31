/*
 * snowflakesOneByOneWithSpecificItemSolver.h
 *
 *  Created on: Aug 29, 2013
 *      Author: amit
 */

#ifndef SNOWFLAKESONEBYONEWITHSPECIFICITEMSOLVER_H_
#define SNOWFLAKESONEBYONEWITHSPECIFICITEMSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class snowflakesOneByOneWithSpecificItemSolver: protected MultiplicativeEffortProduceAndChooseSolver {
public:
	snowflakesOneByOneWithSpecificItemSolver(ProblemInstance* problem, int specificItem) : MultiplicativeEffortProduceAndChooseSolver (problem) {
		this->_specificItem = specificItem;
	}
	virtual ~snowflakesOneByOneWithSpecificItemSolver();
protected:
	SnowFlakeVector* produceManySnowflakes(int numSnowflakes);
	bool candidateAcceptable(SnowFlake& candidate);
	int _specificItem;
};

#endif /* SNOWFLAKESONEBYONEWITHSPECIFICITEMSOLVER_H_ */
