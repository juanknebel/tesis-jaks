/*
 * exhaustiveGreedyAnySimSOBOSolver.h
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#ifndef EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_
#define EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_

#include "../abstract/exhaustiveSOBOSolver.h"

class ExhaustiveGreedyAnySimSOBOSolver : public ExhaustiveSOBOSolver {
public:
	ExhaustiveGreedyAnySimSOBOSolver(double interSimilarityWeight_, double budget) : ExhaustiveSOBOSolver(interSimilarityWeight_, budget) {

	}
	~ExhaustiveGreedyAnySimSOBOSolver() {};

protected:
	SnowFlake pickFlake(Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance& theProblem);
};


#endif /* EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_ */
