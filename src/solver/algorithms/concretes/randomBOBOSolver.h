/*
 * randomBOBOSolver.h
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#ifndef RANDOMBOBOSOLVER_H_
#define RANDOMBOBOSOLVER_H_

#include "randomSOBOSolver.h"

class RandomBOBOSolver : public RandomSOBOSolver {
private:
	static int INITIAL_TRIALS_FOR_MU;
	double mu_;
	void chooseMu(ProblemInstance &theProblem);

public:
	RandomBOBOSolver(double interSimilarityWeight_, double budget) : RandomSOBOSolver(interSimilarityWeight_, budget) {
		this->mu_ = -1.00;
	}
	~RandomBOBOSolver() {};

	bool candidateAcceptable(SnowFlake& candidate, ProblemInstance &theProblem);
};


#endif /* RANDOMBOBOSOLVER_H_ */
