/*
 * solver.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: zero
 */

#include "solver.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool Solver::checkBudgetAndCoverageConstraint(const std::set<int>& currentSnowflake,
		int node) {
	return checkBudgetConstraint(currentSnowflake, node)
			&& checkCoverageConstraint(currentSnowflake, node);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<int>& currentSnowflake,
		int node, int excludeNode){
	return checkBudgetConstraint(currentSnowflake, node)
				&& checkCoverageConstraint(currentSnowflake, node, excludeNode);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<int>& snowflake1,
		const std::set<int>& snowflake2) {
	return checkBudgetConstraint(snowflake1, snowflake2) && checkCoverageConstraint(snowflake1, snowflake2);
}

bool Solver::checkBudgetAndCoverageConstraint(const std::set<int>& snowflake1, const std::set<int>& snowflake2, int excludeNode){
	return checkBudgetConstraint(snowflake1, snowflake2)
				&& checkCoverageConstraint(snowflake1, snowflake2, excludeNode);
}

bool Solver::checkBudgetConstraint(const std::set<int>& currentSnowflake, int newNode) {
	double currentCost = 0;
	for (std::set<int>::iterator it = currentSnowflake.begin(); it != currentSnowflake.end(); ++it) {
		currentCost += this->problem_->getCost(*it);
	}
	bool ret = currentCost + this->problem_->getCost(newNode) <= this->problem_->getbudget();
	return ret;
}

bool Solver::checkBudgetConstraint(const std::set<int>& snowflake1,
		const std::set<int>& snowflake2) {
	int currentCost = 0;
	for (std::set<int>::iterator it = snowflake1.begin(); it != snowflake1.end(); ++it) {
		currentCost += this->problem_->getCost(*it);
		if (currentCost > this->problem_->getbudget()) {
			return false;
		}
	}
	for (std::set<int>::iterator it = snowflake2.begin(); it != snowflake2.end(); ++it) {
		currentCost += this->problem_->getCost(*it);
		if (currentCost > this->problem_->getbudget()) {
			return false;
		}
	}
	return true;

}

bool Solver::checkCoverageConstraint(const std::set<int>& currentSnowflake, int newNode) {
	std::set<int>* coverageCovered;
	coverageCovered = new std::set<int>();
	bool ret = true;

	for (std::set<int>::iterator node = currentSnowflake.begin(); node != currentSnowflake.end(); ++node) {
		const std::set<int>* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				//currentSnowflake is not valid
				ret = false;
			}
			coverageCovered->insert(*cover);
		}
	}
	const std::set<int>* covers = this->problem_->getCover(newNode);
	for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
		if (coverageCovered->find(*cover)!=coverageCovered->end()) {
			// adding this newNode is not valid
			ret = false;
		}
		coverageCovered->insert(*cover);
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<int>& currentSnowflake, int newNode, int excludeNode){
	std::set<int>* coverageCovered;
	coverageCovered = new std::set<int>();
	bool ret = true;

	for (std::set<int>::iterator node = currentSnowflake.begin(); node != currentSnowflake.end(); ++node) {
		if (*node == excludeNode) {
			const std::set<int>* covers = this->problem_->getCover(*node);
			if (covers == NULL) {
				throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
			}
			for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
				if (coverageCovered->find(*cover)!=coverageCovered->end()) {
					//currentSnowflake is not valid
					ret = false;
				}
				coverageCovered->insert(*cover);
			}
		}
	}
	const std::set<int>* covers = this->problem_->getCover(newNode);
	for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
		if (coverageCovered->find(*cover)!=coverageCovered->end()) {
			// adding this newNode is not valid
			ret = false;
		}
		coverageCovered->insert(*cover);
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<int>& snowflake1,
		const std::set<int>& snowflake2) {
	std::set<int>* coverageCovered;
	coverageCovered = new std::set<int>();
	bool ret = true;

	for (std::set<int>::iterator node = snowflake1.begin(); node != snowflake1.end(); ++node) {
		const std::set<int>* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	for (std::set<int>::iterator node = snowflake2.begin(); node != snowflake2.end(); ++node) {
		const std::set<int>* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			coverageCovered->insert(*cover);
		}
	}

	delete coverageCovered;
	return ret;
}

bool Solver::checkCoverageConstraint(const std::set<int>& snowflake1,
		const std::set<int>& snowflake2, int excludeNode) {
	std::set<int>* coverageCovered;
	coverageCovered = new std::set<int>();
	bool ret = true;

	for (std::set<int>::iterator node = snowflake1.begin(); node != snowflake1.end(); ++node) {
		if (excludeNode == *node) {
			continue;
		}
		const std::set<int>* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
			if (coverageCovered->find(*cover)!=coverageCovered->end()) {
				ret =  false;
			}
			if (excludeNode != *cover) {
				coverageCovered->insert(*cover);
			}
		}
	}

	for (std::set<int>::iterator node = snowflake2.begin(); node != snowflake2.end(); ++node) {
		if (excludeNode == *node) {
			continue;
		}
		const std::set<int>* covers = this->problem_->getCover(*node);
		if (covers == NULL) {
			throw Exception(__FILE__, __LINE__, "Error: IllegalStateException(Node  + node +  does not cover anything");
		}
		for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
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

SnowFlake* Solver::pickFlakeGivenPermutation(int pivot, std::vector<int>& clusterMembersPermuted) {
	std::set<int> picked;
	picked.insert(pivot);

	for (std::vector<int>::iterator newMember = clusterMembersPermuted.begin(); newMember != clusterMembersPermuted.end(); ++newMember) {
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
SnowFlake* Solver::pickFlake(int pivot, const std::set<int>& clusterMembers) {
	std::vector<int> membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
    std::sort(membersSorted.begin(), membersSorted.end(), compatCompare(*(this->problem_), this->pivot_));
    //std::sort(membersSorted.begin(), membersSorted.end(), compatCompareSpecificProfile(*(this->problem_), this->pivot_));
	return pickFlakeGivenPermutation(pivot, membersSorted);
}

SnowFlake* Solver::pickFlakeGivenPermutation(int specificItem, int pivot, std::vector<int>& clusterMembersPermuted) {
	std::set<int> picked;
	picked.insert(specificItem);
	picked.insert(pivot);

	for (std::vector<int>::iterator newMember = clusterMembersPermuted.begin(); newMember != clusterMembersPermuted.end(); ++newMember) {
		if (this->checkBudgetAndCoverageConstraint(picked, *newMember)) {
			picked.insert(*newMember);
		}
	}

	SnowFlake* ret = new SnowFlake(picked, this->problem_);
	return ret;
}

SnowFlake* Solver::pickFlake(int specificItem, int pivot, const std::set<int>& clusterMembers) {
	std::vector<int> membersSorted(clusterMembers.begin(), clusterMembers.end());
	this->pivot_ = pivot;
	this->specificItem_ = specificItem;
	std::sort(membersSorted.begin(), membersSorted.end(), compatCompareTwoItems(*(this->problem_), this->specificItem_, this->pivot_));
	return pickFlakeGivenPermutation(specificItem, pivot, membersSorted);
}
