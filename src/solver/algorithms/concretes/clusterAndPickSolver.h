/*
 * clusterAndPickSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef CLUSTERANDPICKSOLVER_H_
#define CLUSTERANDPICKSOLVER_H_

#include "../abstract/solver.h"

class ClusterAndPickSolver: public Solver {
public:
	ClusterAndPickSolver(double interSimilarityWeight_, double budget):Solver(interSimilarityWeight_, budget) {

	}
	~ClusterAndPickSolver();

private:
	std::vector<SnowFlake> solve(ProblemInstance& theProblem, int numSnowFlakes);
	SnowFlake bestSnowFlake(const std::set<Flake>& clusterMembers, ProblemInstance& theProblem);
};

#endif /* CLUSTERANDPICKSOLVER_H_ */
