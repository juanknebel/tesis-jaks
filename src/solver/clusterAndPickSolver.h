/*
 * clusterAndPickSolver.h
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#ifndef CLUSTERANDPICKSOLVER_H_
#define CLUSTERANDPICKSOLVER_H_

#include "solver.h"

class ClusterAndPickSolver: public Solver {
public:
	ClusterAndPickSolver(ProblemInstance* problem):Solver(problem) {

	}
	~ClusterAndPickSolver();

	SnowFlakeVector* solve (int numSnowflakes);
private:
	/**
	 * Finds a good snowflake inside a cluster, by exhaustively checking for each of its members
	 * what is the quality of the snowflake with that member as its center, using {@link #pickFlake}.
	 *
	 * @param clusterMembers the members of a cluster
	 * @return the snowflake picked
	 */
	SnowFlake bestSnowFlake(const std::set<int>& clusterMembers);
};

#endif /* CLUSTERANDPICKSOLVER_H_ */
