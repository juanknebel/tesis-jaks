/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSOLVER_H_
#define RESTRICTEDHACSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class RestrictedHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSolver(ProblemInstance* problem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {

	}
	virtual ~RestrictedHACSolver();

	SnowFlakeVector* produceManySnowflakes(int numToProduce);
protected:
	bool tryMerge(Int2ObjectOpenHashMap* clustering);
};

#endif /* RESTRICTEDHACSOLVER_H_ */
