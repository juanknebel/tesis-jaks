/*
 * sequentialScanSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef SEQUENTIALSCANSOLVER_H_
#define SEQUENTIALSCANSOLVER_H_

#include "../abstract/solver.h"

class SequentialScanSolver: public Solver {
protected:
	std::vector<SnowFlake> solve(ProblemInstance& theProblem, int numSnowFlakes);
	Flake pickRandom(const std::set<Flake>& set);
public:
	SequentialScanSolver(double interSimilarityWeight_, double budget) : Solver(interSimilarityWeight_, budget) {

	}
	~SequentialScanSolver() {};
};

#endif /* SEQUENTIALSCANSOLVER_H_ */
