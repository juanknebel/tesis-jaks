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
#include "../util/exception.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Solver {
protected:
	ProblemInstance* problem_;
	int pivot_;
	int specificItem_;

	bool checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake, int node);
	bool checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake, int node, int excludeNode);
	bool checkBudgetAndCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	bool checkBudgetAndCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2, int excludeNode);
	bool checkBudgetConstraint(const IntSet& currentSnowflake, int newNode);
	bool checkBudgetConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	bool checkCoverageConstraint(const IntSet& currentSnowflake, int newNode);
	bool checkCoverageConstraint(const IntSet& currentSnowflake, int newNode, int excludeNode);
	bool checkCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2);
	bool checkCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2, int excludeNode);
	SnowFlake* pickFlakeGivenPermutation(int pivot, IntVector& clusterMembersPermuted);
	SnowFlake* pickFlake(int pivot, const IntSet& clusterMembers);
	SnowFlake* pickFlakeGivenPermutation(int specificItem, int pivot, IntVector& clusterMembersPermuted);
	SnowFlake* pickFlake(int specificItem, int pivot, const IntSet& clusterMembers);
	
private:
	struct compatCompare {
		compatCompare(ProblemInstance& aProblem, int pivot) : pivot_(pivot), problem_(aProblem) {}
		ProblemInstance& problem_;
		int pivot_;
		inline bool operator() (int node1, int node2) {
			return problem_.getCompat(pivot_, node2) >  problem_.getCompat(pivot_, node1);
		}
	};

	struct compatCompareTwoItems {
			compatCompareTwoItems(ProblemInstance& aProblem, int specificItem, int pivot) : specificItem_(specificItem), pivot_(pivot), problem_(aProblem) {}
			ProblemInstance& problem_;
			int pivot_;
			int specificItem_;
			inline bool operator() (int node1, int node2) {
				double node1_compat =  problem_.getCompat(pivot_, node1) + problem_.getCompat(specificItem_, node1);
				double node2_compat =  problem_.getCompat(pivot_, node2) + problem_.getCompat(specificItem_, node2);
				return node2_compat >  node1_compat;
			}
		};

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
