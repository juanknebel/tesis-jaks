/*
 * RestrictedHACSWithSpecificItemSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSWITHSPECIFICITEMSOLVER_H_
#define RESTRICTEDHACSWITHSPECIFICITEMSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class RestrictedHACSWithSpecificItemSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSWithSpecificItemSolver(ProblemInstance* problem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {

	}
	virtual ~RestrictedHACSWithSpecificItemSolver();

	SnowFlakeVector* produceManySnowflakes(int numToProduce);
protected:
	bool tryMerge(Int2ObjectOpenHashMap& clustering);
};

#endif /* RESTRICTEDHACSOLVER_H_ */
