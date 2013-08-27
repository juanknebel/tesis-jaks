/*
 * exaustiveSOBOSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef EXAUSTIVESOBOSOLVER_H_
#define EXAUSTIVESOBOSOLVER_H_

#include "snowflakesOneByOneSolver.h"

class ExhaustiveSOBOSolver: protected SnowflakesOneByOneSolver {
public:
	ExhaustiveSOBOSolver(ProblemInstance* problem):SnowflakesOneByOneSolver(problem){
		SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = true;

	}
	virtual ~ExhaustiveSOBOSolver();

	int getPivot(IntSet& pivotsUsed, IntSet& possiblePivots);

	int numToProduce(int requestedSnowflakes);
};

#endif /* EXAUSTIVESOBOSOLVER_H_ */
