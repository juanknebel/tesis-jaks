/*
 * solver.h
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "../util/redefinitions.h"
#include "../problemInstance.h"
#include "../snowFlake.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Solver {
protected:
	ProblemInstance* problem_;
	int pivot_;
	bool compare(int o1, int o2);

	bool checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake, int node);
	bool checkBudgetAndCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	bool checkBudgetConstraint(const IntSet& currentSnowflake, int newNode);
	bool checkBudgetConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	bool checkCoverageConstraint(const IntSet& currentSnowflake, int newNode);
	bool checkCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	SnowFlake* pickFlakeGivenPermutation(int pivot, IntVector& clusterMembersPermuted);
	SnowFlake* pickFlake(int pivot, const IntSet& clusterMembers);

public:
	Solver(ProblemInstance* problem) {
		this->problem_ = problem;
		this->pivot_ = 0;
	}
	virtual ~Solver() {}

	/*
	* Finds a set of snowflakes.
	*
	* @param numSnowflakes the number of snowflakes returned
	* @return a set of snowflakes
	*/
	virtual SnowFlakeVector* solve(int numSnowFlakes) = 0;
};

#endif /* SOLVER_H_ */
