/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSOLVER_H_
#define RESTRICTEDHACSOLVER_H_

#include "../abstract/multiplicativeEffortProduceAndChooseSolver.h"
#include "../../../queue/priorityQueue.h"

class RestrictedHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSolver(double interSimilarityWeight_, double budget) :  MultiplicativeEffortProduceAndChooseSolver(interSimilarityWeight_, budget) {

	}
	virtual ~RestrictedHACSolver();

	std::vector<SnowFlake> produceManySnowflakes(int numToProduce, ProblemInstance &theProblem);
	std::vector<SnowFlake> produceManySnowflakes1(int numToProduce, ProblemInstance &theProblem);
protected:
	bool tryMerge(std::map<int, std::set<int>*>* clustering);

private:
	typedef std::vector<PriorityQueue> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDHACSOLVER_H_ */
