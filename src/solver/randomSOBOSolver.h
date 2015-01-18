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
	RandomSOBOSolver(ProblemInstance *problem, Selector* selector) : SnowflakesOneByOneSolver(problem, selector) {
		this->SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;
	}
	~RandomSOBOSolver() {};

	int getPivot(std::set<int>& pivotsUsed, std::set<int>& possiblePivots);
protected:
	int randomNode();
};


#endif /* RANDOMSOBOSOLVER_H_ */
