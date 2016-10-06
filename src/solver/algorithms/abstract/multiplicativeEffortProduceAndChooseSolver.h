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
	MultiplicativeEffortProduceAndChooseSolver(double interSimilarityWeight_, double budget) : ProduceAndChooseSolver (interSimilarityWeight_, budget) {
		this->numCandidatesMultiplier_ = this->DEFAULT_NUMCANDIDATES_MULTIPLIER;
	}
	~MultiplicativeEffortProduceAndChooseSolver() {};
	void setNumCandidatesMultiplier(double numCandidatesMultiplier);
	virtual int numToProduce(int requestedSnowFlake);
};


#endif /* MULTIPLICATIVEEFFORTPRODUCEANDCHOOSESOLVER_H_ */
