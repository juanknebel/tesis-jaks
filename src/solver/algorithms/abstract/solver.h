/*
 * solver.h
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "../../../problem/problemInstance.h"
#include "../../../problem/snowFlake.h"
#include "../../../util/system/exception.h"

class Solver {
protected:
	Flake pivot_;
	Flake specificItem_;
	double interSimilarityWeight_;
	double budget_;

	bool checkBudgetAndCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake node, ProblemInstance &theProblem);
	bool checkBudgetAndCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake node, Flake excludeNode,
                                              ProblemInstance &theProblem);
	bool checkBudgetAndCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2,
                                              ProblemInstance &theProblem);
	bool checkBudgetAndCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, Flake excludeNode,
                                              ProblemInstance &theProblem);
	bool checkBudgetConstraint(const std::set<Flake> &currentSnowflake, Flake newNode);
	bool checkBudgetConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2);
	bool checkCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake newNode, ProblemInstance &theProblem);
	bool checkCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake newNode, Flake excludeNode,
                                     ProblemInstance &theProblem);
	bool checkCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, ProblemInstance &theProblem);
	bool checkCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, Flake excludeNode,
                                     ProblemInstance &theProblem);
	SnowFlake
	pickFlakeGivenPermutation(Flake pivot, std::vector<Flake> &clusterMembersPermuted, ProblemInstance &theProblem);
	SnowFlake pickFlakeGivenPermutation(Flake specificItem, Flake pivot, std::vector<Flake> &clusterMembersPermuted,
                                            ProblemInstance &theProblem);
	virtual SnowFlake pickFlake(Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem);
    virtual SnowFlake pickFlake(Flake specificItem, Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem);
	//SnowFlake pickFlakeSpecificProfile(Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem);
	//SnowFlake pickFlakeSpecificProfile(Flake specificItem, Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem);
	//virtual std::vector<SnowFlake> solve(ProblemInstance& theProblem, int numSnowFlakes) const = 0;
	virtual std::vector<SnowFlake> solve(ProblemInstance& theProblem, int numSnowFlakes) = 0;

private:
	struct compatCompare {
		compatCompare(ProblemInstance& aProblem, Flake pivot) : pivot_(pivot), problem_(aProblem) {}
		ProblemInstance& problem_;
		Flake pivot_;
		inline bool operator() (Flake node1, Flake node2) {
			return Flake::getCompat(pivot_, node2, problem_) > Flake::getCompat(pivot_, node1, problem_);
		}
	};

	struct compatCompareTwoItems {
		compatCompareTwoItems(ProblemInstance& aProblem, Flake specificItem, Flake pivot) : specificItem_(specificItem), pivot_(pivot), problem_(aProblem) {}
		ProblemInstance& problem_;
		Flake pivot_;
		Flake specificItem_;
		inline bool operator() (Flake node1, Flake node2) {
			double node1_compat =  Flake::getCompat(pivot_, node1, problem_) + Flake::getCompat(specificItem_, node1, problem_);
			double node2_compat =  Flake::getCompat(pivot_, node2, problem_) + Flake::getCompat(specificItem_, node2, problem_);
			return node2_compat >  node1_compat;
		}
	};

	struct compatCompareSpecificProfile {
		compatCompareSpecificProfile(ProblemInstance& aProblem, Flake pivot) : pivot_(pivot), problem_(aProblem) {}
		ProblemInstance& problem_;
		Flake pivot_;
		inline bool operator() (int node1, int node2) {
			return problem_.getCompatWithSpecificProfile(pivot_.getId(), node2) >  problem_.getCompatWithSpecificProfile(pivot_.getId(), node1);
		}
	};

public:
	Solver(double interSimilarityWeight_, double budget) {
		this->pivot_ = Flake();
		this->interSimilarityWeight_ = interSimilarityWeight_;
		this->specificItem_ = Flake();
		this->budget_ = budget;
	}
	virtual ~Solver() {}

	static std::vector<SnowFlake> execute(ProblemInstance& theProblem, Solver& solver, int numFlakes);
};

#endif /* SOLVER_H_ */
