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
	ExhaustiveGreedyAnySimSOBOSolver(ProblemInstance* problem) : ExhaustiveSOBOSolver(problem) {

	}
	~ExhaustiveGreedyAnySimSOBOSolver() {};

protected:
	SnowFlake pickFlake(int pivot, const std::set<int>& clusterMembers);
};


#endif /* EXHAUSTIVEGREEDYANYSIMSOBOSOLVER_H_ */
