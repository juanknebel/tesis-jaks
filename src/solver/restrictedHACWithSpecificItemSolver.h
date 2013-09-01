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
	RestrictedHACSWithSpecificItemSolver(ProblemInstance* problem, int specificItem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {
		this->_specificItem = specificItem;
	}
	virtual ~RestrictedHACSWithSpecificItemSolver();

	SnowFlakeVector* produceManySnowflakes(int numToProduce);
protected:
	bool tryMerge(Int2ObjectOpenHashMap& clustering);
	int _specificItem;
};

#endif /* RESTRICTEDHACSOLVER_H_ */
