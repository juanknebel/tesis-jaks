/*
 * sequentialScanSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef SEQUENTIALSCANSOLVER_H_
#define SEQUENTIALSCANSOLVER_H_

#include "solver.h"

class SequentialScanSolver: public Solver {
public:
	SequentialScanSolver(ProblemInstance* problem):Solver(problem) {

	}
	~SequentialScanSolver() {};

	SnowFlakeVector* solve(int numSnowflakes);
	int pickRandom(const std::set<int>& set);
};

#endif /* SEQUENTIALSCANSOLVER_H_ */
