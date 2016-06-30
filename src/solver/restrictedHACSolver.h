/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSOLVER_H_
#define RESTRICTEDHACSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"
#include "../queue/priorityQueue.h"

class RestrictedHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSolver(ProblemInstance* problem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {

	}
	virtual ~RestrictedHACSolver();

    SnowFlakeVector* produceManySnowflakes(int numToProduce);
    SnowFlakeVector* produceManySnowflakes1(int numToProduce);
protected:
	bool tryMerge(MapIntIntSet* clustering);

private:
    typedef std::vector<PriorityQueue*> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDHACSOLVER_H_ */
