/*
 * solver.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#include "solver.h"

using namespace std;

bool Solver::checkBudgetAndCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake node,
											  ProblemInstance &theProblem)
{
	return checkBudgetConstraint(currentSnowflake, node)
	       && checkCoverageConstraint(currentSnowflake, node, theProblem);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake node, Flake excludeNode,
											  ProblemInstance &theProblem)
{
	return checkBudgetConstraint(currentSnowflake, node)
	       && checkCoverageConstraint(currentSnowflake, node, excludeNode, theProblem);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2,
											  ProblemInstance &theProblem)
{
	return checkBudgetConstraint(snowflake1, snowflake2) &&
		   checkCoverageConstraint(snowflake1, snowflake2, theProblem);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, Flake excludeNode,
											  ProblemInstance &theProblem)
{
	return checkBudgetConstraint(snowflake1, snowflake2)
	       && checkCoverageConstraint(snowflake1, snowflake2, excludeNode, theProblem);
}

bool Solver::checkBudgetConstraint(const std::set<Flake> &currentSnowflake, Flake newNode)
{
	double currentCost = 0;

	for (auto aFlake : currentSnowflake) {
		currentCost += aFlake.getCost();
	}

	bool ret = currentCost + newNode.getCost() <= budget_;
	return ret;
}

bool Solver::checkBudgetConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2)
{
	int currentCost = 0;

	for (auto aFlake : snowflake1) {
		currentCost += aFlake.getCost();

		if (currentCost > budget_) {
			return false;
		}
	}

	for (auto aFlake : snowflake2) {
		currentCost += aFlake.getCost();

		if (currentCost > budget_) {
			return false;
		}
	}

	return true;

}

bool Solver::checkCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake newNode, ProblemInstance &theProblem)
{
	std::set<int> coverageCovered;
	bool ret = true;

	for (auto aFlake : currentSnowflake) {
		const std::set<int>* covers = theProblem.getCover(aFlake.getId());

		if (covers == nullptr) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}

		for (auto cover : *covers) {
			if (coverageCovered.find(cover)!=coverageCovered.end()) {
				//currentSnowflake is not valid
				ret = false;
			}

			coverageCovered.insert(cover);
		}
	}

	const std::set<int>* covers = theProblem.getCover(newNode.getId());

	for (auto cover : *covers) {
		if (coverageCovered.find(cover)!=coverageCovered.end()) {
			// adding this newNode is not valid
			ret = false;
		}

		coverageCovered.insert(cover);
	}

	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<Flake> &currentSnowflake, Flake newNode, Flake excludeNode,
									 ProblemInstance &theProblem)
{
	std::set<int> coverageCovered;
	bool ret = true;

	for (auto aFlake : currentSnowflake) {
		if (aFlake == excludeNode) {
			const std::set<int>* covers = theProblem.getCover(aFlake.getId());

			if (covers == nullptr) {
				throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
			}

			for (auto cover : *covers) {
				if (coverageCovered.find(cover)!=coverageCovered.end()) {
					//currentSnowflake is not valid
					ret = false;
				}

				coverageCovered.insert(cover);
			}
		}
	}

	const std::set<int>* covers = theProblem.getCover(newNode.getId());

	for (auto cover : *covers) {
		if (coverageCovered.find(cover)!=coverageCovered.end()) {
			// adding this newNode is not valid
			ret = false;
		}

		coverageCovered.insert(cover);
	}

	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, ProblemInstance &theProblem)
{
	std::set<int> coverageCovered;
	bool ret = true;

	for (auto aFlake : snowflake1) {
		const std::set<int>* covers = theProblem.getCover(aFlake.getId());

		if (covers == nullptr) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}

		for (auto cover : *covers) {
			if (coverageCovered.find(cover)!=coverageCovered.end()) {
				ret =  false;
			}

			coverageCovered.insert(cover);
		}
	}

	for (auto aFlake : snowflake2) {
		const std::set<int>* covers = theProblem.getCover(aFlake.getId());

		if (covers == nullptr) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}

		for (auto cover : *covers) {
			if (coverageCovered.find(cover)!=coverageCovered.end()) {
				ret =  false;
			}

			coverageCovered.insert(cover);
		}
	}

	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<Flake> &snowflake1, const std::set<Flake> &snowflake2, Flake excludeNode,
									 ProblemInstance &theProblem)
{
	std::set<int> coverageCovered;
	bool ret = true;

	for (auto aFlake : snowflake1) {
		if (excludeNode == aFlake) {
			continue;
		}

		const std::set<int>* covers = theProblem.getCover(aFlake.getId());

		if (covers == nullptr) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}

		for (auto cover : *covers) {
			if (coverageCovered.find(cover)!=coverageCovered.end()) {
				ret =  false;
			}

			if (excludeNode.getId() != cover) {
				coverageCovered.insert(cover);
			}
		}
	}

	for (auto aFlake : snowflake2) {
		if (excludeNode == aFlake) {
			continue;
		}

		const std::set<int>* covers = theProblem.getCover(aFlake.getId());

		if (covers == nullptr) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}

		for (auto cover : *covers) {
			if (coverageCovered.find(cover)!=coverageCovered.end()) {
				ret =  false;
			}

			if (excludeNode.getId() != cover) {
				coverageCovered.insert(cover);
			}
		}
	}

	return ret;
}

SnowFlake Solver::pickFlakeGivenPermutation(Flake pivot, std::vector<Flake> &clusterMembersPermuted, ProblemInstance &theProblem)
{
	std::set<Flake> picked;
	picked.insert(pivot);

	for (auto aNewFlake : clusterMembersPermuted) {
		if (this->checkBudgetAndCoverageConstraint(picked, aNewFlake, theProblem)) {
			picked.insert(aNewFlake);
		}
	}

	SnowFlake ret = SnowFlake(picked);
	return ret;
}

/**
 * Builds a good snowflake with an element at its center.
 *
 * @param pivot central element
 * @param clusterMembers possible other elements in the cluster
 * @return a good snowflake containing the central element
 */
SnowFlake Solver::pickFlake(Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem)
{
	std::vector<Flake> membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
	std::sort(membersSorted.begin(), membersSorted.end(), compatCompare(theProblem, this->pivot_));
	//std::sort(membersSorted.begin(), membersSorted.end(), compatCompareSpecificProfile(*(this->problem_), this->pivot_));
	return pickFlakeGivenPermutation(pivot, membersSorted, theProblem);
}

SnowFlake Solver::pickFlakeGivenPermutation(Flake specificItem, Flake pivot, std::vector<Flake> &clusterMembersPermuted,
											ProblemInstance &theProblem)
{
	std::set<Flake> picked;
	picked.insert(specificItem);
	picked.insert(pivot);

	for (auto newFlake : clusterMembersPermuted) {
		if (this->checkBudgetAndCoverageConstraint(picked, newFlake, theProblem)) {
			picked.insert(newFlake);
		}
	}

	SnowFlake ret = SnowFlake(picked);
	return ret;
}

SnowFlake Solver::pickFlake(Flake specificItem, Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance &theProblem)
{
	std::vector<Flake> membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
	this->specificItem_ = specificItem;
	std::sort(membersSorted.begin(), membersSorted.end(), compatCompareTwoItems(theProblem, this->specificItem_, this->pivot_));
	return pickFlakeGivenPermutation(specificItem, pivot, membersSorted, theProblem);
}

std::vector<SnowFlake> Solver::execute(ProblemInstance &theProblem, Solver &solver, int numFlakes) {
	return solver.solve(theProblem, numFlakes);
}
