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
	ExhaustiveSOBOSolver(double interSimilarityWeight_, double budget):SnowflakesOneByOneSolver(interSimilarityWeight_, budget) {
		SnowflakesOneByOneSolver::SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = true;

	}
	~ExhaustiveSOBOSolver() {};

	Flake getPivot(std::set<Flake> &pivotsUsed, std::set<Flake> &possiblePivots, ProblemInstance& theProblem);

	int numToProduce(int requestedSnowflakes);
};

#endif /* EXAUSTIVESOBOSOLVER_H_ */
