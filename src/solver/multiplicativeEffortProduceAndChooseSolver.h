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
	static Double DEFAULT_NUMCANDIDATES_MULTIPLIER;
	Double numCandidatesMultiplier_;
public:
	MultiplicativeEffortProduceAndChooseSolver(ProblemInstance* problem) : ProduceAndChooseSolver (problem) {
		this->numCandidatesMultiplier_ = this->DEFAULT_NUMCANDIDATES_MULTIPLIER;
	}
	~MultiplicativeEffortProduceAndChooseSolver();
	void setNumCandidatesMultiplier(Double numCandidatesMultiplier);
	int numToProduce(int requestedSnowFlake);
};


#endif /* MULTIPLICATIVEEFFORTPRODUCEANDCHOOSESOLVER_H_ */
