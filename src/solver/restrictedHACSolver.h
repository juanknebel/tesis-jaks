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
	RestrictedHACSolver(ProblemInstance* problem, Selector* selector) : MultiplicativeEffortProduceAndChooseSolver(problem, selector) {

	}
	virtual ~RestrictedHACSolver();

    SnowFlakeVector* produceManySnowflakesSingleCluster(int numToProduce);
    SnowFlakeVector* produceManySnowflakes(int numToProduce);
protected:
	bool tryMerge(MapIntIntSet* clustering);

private:
    double sim(IntSet* snowflake1, IntSet* snowflake2);
    typedef std::vector<PriorityQueue*> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDHACSOLVER_H_ */
