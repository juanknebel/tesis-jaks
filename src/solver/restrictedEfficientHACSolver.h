/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDEFFICIENTHACSOLVER_H_
#define RESTRICTEDEFFICIENTHACSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"
#include "../queue/priorityQueue.h"

class RestrictedEfficientHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedEfficientHACSolver(ProblemInstance* problem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {

	}
	virtual ~RestrictedEfficientHACSolver();

	SnowFlakeVector* produceManySnowflakes(int numToProduce);

private:
	double sim(std::set<int>* snowflake1, std::set<int>* snowflake2);
	typedef std::vector<PriorityQueue*> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDEFFICIENTHACSOLVER_H_ */
