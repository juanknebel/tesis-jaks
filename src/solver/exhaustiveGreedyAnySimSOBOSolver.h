/*
 * exhaustiveGreedyAnySimSOBOSolver.h
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#ifndef EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_
#define EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_

#include "exhaustiveSOBOSolver.h"

class ExhaustiveGreedyAnySimSOBOSolver : public ExhaustiveSOBOSolver {
	public:
	ExhaustiveGreedyAnySimSOBOSolver(ProblemInstance* problem, Selector* selector) : ExhaustiveSOBOSolver(problem, selector) {

	}
	~ExhaustiveGreedyAnySimSOBOSolver() {};

	protected:
	SnowFlake* pickFlake(int pivot, const IntSet& clusterMembers);
};


#endif /* EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_ */
