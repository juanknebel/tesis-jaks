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
	ExhaustiveGreedySumSimSOBOSolver(ProblemInstance* problem) : ExhaustiveSOBOSolver(problem) {

	}
	~ExhaustiveGreedySumSimSOBOSolver() {};

protected:
	SnowFlake pickFlake(int pivot, const std::set<int>& clusterMembers);
};


#endif /* EXHAUSTIVEGREEDYSUMSIMSOBOSOLVER_H_ */
