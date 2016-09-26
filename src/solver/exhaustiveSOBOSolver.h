/*
 * exaustiveSOBOSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef EXAUSTIVESOBOSOLVER_H_
#define EXAUSTIVESOBOSOLVER_H_

#include "snowflakesOneByOneSolver.h"

class ExhaustiveSOBOSolver: public SnowflakesOneByOneSolver {
public:
	ExhaustiveSOBOSolver(ProblemInstance* problem):SnowflakesOneByOneSolver(problem) {
		SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = true;

	}
	~ExhaustiveSOBOSolver() {};

	int getPivot(std::set<int>& pivotsUsed, std::set<int>& possiblePivots);

	int numToProduce(int requestedSnowflakes);
};

#endif /* EXAUSTIVESOBOSOLVER_H_ */
