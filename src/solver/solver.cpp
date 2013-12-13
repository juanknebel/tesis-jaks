/*
 * solver.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#include "solver.h"
#include "../util/Logger.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake,
		int node) {
	return checkBudgetConstraint(currentSnowflake, node)
			&& checkCoverageConstraint(currentSnowflake, node);
}

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& currentSnowflake,
		int node, int excludeNode){
	return checkBudgetConstraint(currentSnowflake, node)
				&& checkCoverageConstraint(currentSnowflake, node, excludeNode);
}

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& snowflake1,
		const IntSet& snowflake2) {
	return checkBudgetConstraint(snowflake1, snowflake2) && checkCoverageConstraint(snowflake1, snowflake2);
}

bool Solver::checkBudgetAndCoverageConstraint(const IntSet& snowflake1, const IntSet& snowflake2, int excludeNode){
	return checkBudgetConstraint(snowflake1, snowflake2)
				&& checkCoverageConstraint(snowflake1, snowflake2, excludeNode);
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
		const IntSet* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				//currentSnowflake is not valid
				ret = false;
			}
			coverageCovered->insert(*cover);
		}
	}
	const IntSet* covers = this->problem_->getCover(newNode);
	for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
		if (coverageCovered->find(*cover)!=coverageCovered->end()) {
			// adding this newNode is not valid
			ret = false;
		}
		coverageCovered->insert(*cover);
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const IntSet& currentSnowflake, int newNode, int excludeNode){
	IntSet* coverageCovered;
	coverageCovered = new IntSet();
	bool ret = true;

	for (IntSet::iterator node = currentSnowflake.begin(); node != currentSnowflake.end(); ++node) {
		if (*node == excludeNode) {
			const IntSet* covers = this->problem_->getCover(*node);
			if (covers == NULL) {
				throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
			}
			for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
				if (coverageCovered->find(*cover)!=coverageCovered->end()) {
					//currentSnowflake is not valid
					ret = false;
				}
				coverageCovered->insert(*cover);
			}
		}
	}
	const IntSet* covers = this->problem_->getCover(newNode);
	for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
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
		const IntSet* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	for (IntSet::iterator node = snowflake2.begin(); node != snowflake2.end(); ++node) {
		const IntSet* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const IntSet& snowflake1,
		const IntSet& snowflake2, int excludeNode) {
	IntSet* coverageCovered;
	coverageCovered = new IntSet();
	bool ret = true;

	for (IntSet::iterator node = snowflake1.begin(); node != snowflake1.end(); ++node) {
		if (excludeNode == *node) {
			continue;
		}
		const IntSet* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			if (excludeNode != *cover) {
				coverageCovered->insert(*cover);
			}
		}
	}

	for (IntSet::iterator node = snowflake2.begin(); node != snowflake2.end(); ++node) {
		if (excludeNode == *node) {
			continue;
		}
		const IntSet* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			if (excludeNode != *cover) {
				coverageCovered->insert(*cover);
			}
		}
	}

	delete coverageCovered;
	return ret;
}

SnowFlake* Solver::pickFlakeGivenPermutation(int pivot, IntVector& clusterMembersPermuted) {
	IntSet picked;
	picked.insert(pivot);

	for (IntVector::iterator newMember = clusterMembersPermuted.begin(); newMember != clusterMembersPermuted.end(); ++newMember) {
		if (this->checkBudgetAndCoverageConstraint(picked, *newMember)) {
			picked.insert(*newMember);
		}
	}

	SnowFlake* ret = new SnowFlake(picked, this->problem_);
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
	IntVector membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
	std::sort(membersSorted.begin(), membersSorted.end(), compatCompare(*(this->problem_), this->pivot_));
	return pickFlakeGivenPermutation(pivot, membersSorted);
}

SnowFlake* Solver::pickFlakeGivenPermutation(int specificItem, int pivot, IntVector& clusterMembersPermuted) {
	IntSet picked;
	picked.insert(specificItem);
	picked.insert(pivot);

	for (IntVector::iterator newMember = clusterMembersPermuted.begin(); newMember != clusterMembersPermuted.end(); ++newMember) {
		if (this->checkBudgetAndCoverageConstraint(picked, *newMember)) {
			picked.insert(*newMember);
		}
	}

	SnowFlake* ret = new SnowFlake(picked, this->problem_);
	return ret;
}

SnowFlake* Solver::pickFlake(int specificItem, int pivot, const IntSet& clusterMembers) {
	IntVector membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
	this->specificItem_ = specificItem;
	std::sort(membersSorted.begin(), membersSorted.end(), compatCompareTwoItems(*(this->problem_), this->specificItem_, this->pivot_));
	return pickFlakeGivenPermutation(specificItem, pivot, membersSorted);
}
