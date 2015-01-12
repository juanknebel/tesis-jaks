/*
 * exhaustiveGreedySumSimSOBOSolver.h
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#ifndef EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_
#define EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_

#include "exhaustiveSOBOSolver.h"

class ExhaustiveGreedySumSimSOBOSolver : public ExhaustiveSOBOSolver {
public:
	ExhaustiveGreedySumSimSOBOSolver(ProblemInstance* problem, Selector* selector) : ExhaustiveSOBOSolver(problem, selector) {

	}
	~ExhaustiveGreedySumSimSOBOSolver() {};

	protected:
	SnowFlake* pickFlake(int pivot, const IntSet& clusterMembers);
};


#endif /* EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_ */
