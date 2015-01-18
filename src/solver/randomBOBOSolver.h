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

	double chooseMu();

public:
	RandomBOBOSolver(ProblemInstance* problem, Selector* selector) : RandomSOBOSolver(problem, selector) {
		this->mu_ = chooseMu();
	}
	~RandomBOBOSolver() {};

	bool candidateAcceptable(SnowFlake& candidate);
};


#endif /* RANDOMBOBOSOLVER_H_ */
