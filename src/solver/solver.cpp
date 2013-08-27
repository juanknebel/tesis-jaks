/*
 * solver.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#include "solver.h"

using namespace std;

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake,
		int node) {
	return checkBudgetConstraint(currentSnowflake, node)
			&& checkCoverageConstraint(currentSnowflake, node);
}

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& snowflake1,
		const IntSet& snowflake2) {
	return checkBudgetConstraint(snowflake1, snowflake2)
			&& checkCoverageConstraint(snowflake1, snowflake2);
}

bool Solver::checkBudgetConstraint(const IntSet& currentSnowflake, int newNode) {
	double currentCost = 0;
	for (IntSet::iterator it = currentSnowflake.begin(); it != currentSnowflake.end(); ++it) {
			currentCost += this->problem_->getCost(*it);
	}
	bool ret = currentCost + this->problem_->getCost(newNode) <= this->problem_->getbudget();
	return ret;
}

bool Solver::checkBudgetConstraint(const IntSet& snowflake1,
		const IntSet& snowflake2) {
	int currentCost = 0;
	for (IntSet::iterator it = snowflake1.begin(); it != snowflake1.end(); ++it) {
		currentCost += this->problem_->getCost(*it);
		if (currentCost > this->problem_->getbudget()) {
			return false;
		}
	}
	for (IntSet::iterator it = snowflake2.begin(); it != snowflake2.end(); ++it) {
		currentCost += this->problem_->getCost(*it);
		if (currentCost > this->problem_->getbudget()) {
			return false;
		}
	}
	return true;

}

bool Solver::checkCoverageConstraint(const IntSet& currentSnowflake, int newNode) {
	IntSet* coverageCovered;
	coverageCovered = new IntSet();
	bool ret = true;

	for (IntSet::iterator node = currentSnowflake.begin(); node != currentSnowflake.end(); ++node) {
		IntSet& covers = this->problem_->getCover(*node);
//		if (covers == NULL) {
//			throw 0; //new IllegalStateException("Node " + node + " does not cover anything");
//		}
		for (IntSet::iterator cover = covers.begin(); cover != covers.end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				// currentSnowflake is not valid
				ret = false;
			}
			coverageCovered->insert(*cover);
		}
	}
	IntSet& covers = this->problem_->getCover(newNode);
	for (IntSet::iterator cover = covers.begin(); cover != covers.end(); ++cover) {
		if (coverageCovered->find(*cover)!=coverageCovered->end()) {
			// adding this newNode is not valid
			ret = false;
		}
		coverageCovered->insert(*cover);
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const IntSet& snowflake1,
		const IntSet& snowflake2) {
	IntSet* coverageCovered;
	coverageCovered = new IntSet();
	bool ret = true;

	for (IntSet::iterator node = snowflake1.begin(); node != snowflake1.end(); ++node) {
		IntSet& covers = this->problem_->getCover(*node);
//		if (covers == NULL) {
//			throw 0; //new IllegalStateException("Node " + node + " does not cover anything");
//		}
		for (IntSet::iterator cover = covers.begin(); cover != covers.end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	for (IntSet::iterator node = snowflake2.begin(); node != snowflake2.end(); ++node) {
		IntSet& covers = this->problem_->getCover(*node);
//		if (covers == NULL) {
//			throw 0;// new IllegalStateException("Node " + node + " does not cover anything");
//		}
		for (IntSet::iterator cover = covers.begin(); cover != covers.end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	delete coverageCovered;
	return ret;
}

SnowFlake* Solver::pickFlakeGivenPermutation(int pivot, IntVector& clusterMembersPermuted) {
	IntSet* picked;
	picked = new IntSet();
	picked->insert(pivot);

	for (IntVector::iterator newMember = clusterMembersPermuted.begin(); newMember != clusterMembersPermuted.end(); ++newMember) {
		if (this->checkBudgetAndCoverageConstraint(*picked, *newMember)) {
			picked->insert(*newMember);
		}
	}

	SnowFlake* ret;
	ret = new SnowFlake(*picked, this->problem_);
	return ret;
}

/**
 * Builds a good snowflake with an element at its center.
 *
 * @param pivot central element
 * @param clusterMembers possible other elements in the cluster
 * @return a good snowflake containing the central element
 */
SnowFlake* Solver::pickFlake(int pivot, const IntSet& clusterMembers) {

	// Sort clusterMembers by decreasing compatibility
	IntVector membersSorted;
	this->pivot_ = pivot;
	std::copy(clusterMembers.begin(), clusterMembers.end(), std::back_inserter(membersSorted));
	//std::sort(membersSorted.begin(), membersSorted.end(), this->compare);
	return pickFlakeGivenPermutation(pivot, membersSorted);
}

bool Solver::compare(int o1, int o2)
{
	return this->problem_->getCompat(this->pivot_, o2) >  this->problem_->getCompat(this->pivot_, o1);
}

