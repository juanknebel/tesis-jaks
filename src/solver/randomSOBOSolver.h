/*
 * randomSOBOSolver.h
 *
 *  Created on: 14/08/2013
 *      Author: jknebel
 */

#ifndef RANDOMSOBOSOLVER_H_
#define RANDOMSOBOSOLVER_H_

#include "snowflakesOneByOneSolver.h"
class RandomSOBOSolver : public SnowflakesOneByOneSolver {
public:
	RandomSOBOSolver(ProblemInstance *problem) : SnowflakesOneByOneSolver(problem) {
		this->SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;
		srand(57);
	}
	~RandomSOBOSolver() {};

	int getPivot(IntSet& pivotsUsed, IntSet& possiblePivots);
protected:
	int randomNode();
};


#endif /* RANDOMSOBOSOLVER_H_ */
