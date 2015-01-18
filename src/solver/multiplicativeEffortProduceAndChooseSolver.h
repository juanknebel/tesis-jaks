/*
 * multiplicativeEffortProduceAndChooseSolver.h
 *
 *  Created on: 10/08/2013
 *      Author: zero
 */

#ifndef MULTIPLICATIVEEFFORTPRODUCEANDCHOOSESOLVER_H_
#define MULTIPLICATIVEEFFORTPRODUCEANDCHOOSESOLVER_H_

#include "produceAndChooseSolver.h"

class MultiplicativeEffortProduceAndChooseSolver: public ProduceAndChooseSolver {
protected:
	static double DEFAULT_NUMCANDIDATES_MULTIPLIER;
	double numCandidatesMultiplier_;
public:
	MultiplicativeEffortProduceAndChooseSolver(ProblemInstance* problem, Selector* selector) : ProduceAndChooseSolver (problem, selector) {
		this->numCandidatesMultiplier_ = this->DEFAULT_NUMCANDIDATES_MULTIPLIER;
	}
	~MultiplicativeEffortProduceAndChooseSolver() {};
	void setNumCandidatesMultiplier(double numCandidatesMultiplier);
	int numToProduce(int requestedSnowFlake);
};


#endif /* MULTIPLICATIVEEFFORTPRODUCEANDCHOOSESOLVER_H_ */
