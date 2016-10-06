/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDEFFICIENTHACSOLVER_H_
#define RESTRICTEDEFFICIENTHACSOLVER_H_

#include "../abstract/multiplicativeEffortProduceAndChooseSolver.h"
#include "../../../queue/priorityQueue.h"

class RestrictedEfficientHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedEfficientHACSolver(double interSimilarityWeight_, double budget) :  MultiplicativeEffortProduceAndChooseSolver(interSimilarityWeight_, budget) {

	}
	virtual ~RestrictedEfficientHACSolver();

	std::vector<SnowFlake> produceManySnowflakes(int numToProduce, ProblemInstance &theProblem);

private:
	double sim(std::set<Flake> &snowflake1, std::set<Flake> &snowflake2, ProblemInstance &theProblem);
	typedef std::vector<PriorityQueue> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDEFFICIENTHACSOLVER_H_ */
