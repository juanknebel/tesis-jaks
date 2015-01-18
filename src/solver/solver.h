/*
 * solver.h
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "../problem/problemInstance.h"
#include "../problem/snowFlake.h"
#include "../util/system/exception.h"
#include "selector/selector.h"

typedef std::vector<SnowFlake> SnowFlakeVector;

class Solver {
protected:
	ProblemInstance* problem_;
	int pivot_;
	int specificItem_;
    double interSimilarityWeight_;
	Selector* theSelectorStrategy_;

	bool checkBudgetAndCoverageConstraint(const std::set<int>& currentSnowflake, int node);
	bool checkBudgetAndCoverageConstraint(const std::set<int>& currentSnowflake, int node, int excludeNode);
	bool checkBudgetAndCoverageConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2);
	bool checkBudgetAndCoverageConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2, int excludeNode);
	bool checkBudgetConstraint(const std::set<int>& currentSnowflake, int newNode);
	bool checkBudgetConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2);
	bool checkCoverageConstraint(const std::set<int>& currentSnowflake, int newNode);
	bool checkCoverageConstraint(const std::set<int>& currentSnowflake, int newNode, int excludeNode);
	bool checkCoverageConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2);
	bool checkCoverageConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2, int excludeNode);
    SnowFlake* pickFlakeGivenPermutation(int pivot, std::vector<int>& clusterMembersPermuted);
    SnowFlake* pickFlakeGivenPermutation(int specificItem, int pivot, std::vector<int>& clusterMembersPermuted);
	SnowFlake* pickFlake(int pivot, const std::set<int>& clusterMembers);
    SnowFlake* pickFlake(int specificItem, int pivot, const std::set<int>& clusterMembers);
    SnowFlake* pickFlakeSpecificProfile(int pivot, const std::set<int>& clusterMembers);
    SnowFlake* pickFlakeSpecificProfile(int specificItem, int pivot, const std::set<int>& clusterMembers);
	
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

    struct compatCompareSpecificProfile {
        compatCompareSpecificProfile(ProblemInstance& aProblem, int pivot) : pivot_(pivot), problem_(aProblem) {}
        ProblemInstance& problem_;
        int pivot_;
        inline bool operator() (int node1, int node2) {
            return problem_.getCompatWithSpecificProfile(pivot_, node2) >  problem_.getCompatWithSpecificProfile(pivot_, node1);
        }
    };

public:
	Solver(ProblemInstance* problem, Selector* selector) {
		this->problem_ = problem;
		this->pivot_ = 0;
		this->theSelectorStrategy_ = selector;
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
