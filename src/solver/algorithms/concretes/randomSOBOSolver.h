/*
 * randomSOBOSolver.h
 *
 *  Created on: 14/08/2013
 *      Author: jknebel
 */

#ifndef RANDOMSOBOSOLVER_H_
#define RANDOMSOBOSOLVER_H_

#include "../abstract/snowflakesOneByOneSolver.h"
class RandomSOBOSolver : public SnowflakesOneByOneSolver {
public:
	RandomSOBOSolver(double interSimilarityWeight_, double budget) : SnowflakesOneByOneSolver(interSimilarityWeight_, budget) {
		this->SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS = false;
		srand(57);
	}
	~RandomSOBOSolver() {};

	Flake getPivot(std::set<Flake>& pivotsUsed, std::set<Flake>& possiblePivots, ProblemInstance& theProblem);
protected:
	Flake randomNode(ProblemInstance& theProblem);
};


#endif /* RANDOMSOBOSOLVER_H_ */
