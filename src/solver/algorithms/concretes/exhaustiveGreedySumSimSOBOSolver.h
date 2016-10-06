/*
 * exhaustiveGreedySumSimSOBOSolver.h
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#ifndef EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_
#define EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_

#include "../abstract/exhaustiveSOBOSolver.h"

class ExhaustiveGreedySumSimSOBOSolver : public ExhaustiveSOBOSolver {
public:
	ExhaustiveGreedySumSimSOBOSolver(double interSimilarityWeight_, double budget) : ExhaustiveSOBOSolver(interSimilarityWeight_, budget) {

	}
	~ExhaustiveGreedySumSimSOBOSolver() {};

protected:
	SnowFlake pickFlake(Flake pivot, const std::set<Flake>& clusterMembers, ProblemInstance& theProblem);
};


#endif /* EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_ */
