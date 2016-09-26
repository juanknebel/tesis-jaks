/*
 * RestrictedHACSWithSpecificItemSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACWithSpecificItemSolver.h"

RestrictedHACSWithSpecificItemSolver::~RestrictedHACSWithSpecificItemSolver()
{
	// TODO Auto-generated destructor stub
}

SnowFlakeVector* RestrictedHACSWithSpecificItemSolver::produceManySnowflakes(int numToProduce)
{
	if (this->problem_->numNodes() < numToProduce) {
		throw Exception(__FILE__, __LINE__, "Too few nodes");
	}

	// Put each item with specific item in its own cluster
	std::map<int, std::set<int>*> clustering = std::map<int, std::set<int>*>();
	std::set<int> ids = this->problem_->getIds();

	for (std::set<int>::iterator it = ids.begin(); it != ids.end(); ++it) {
		// Make sure all singleton clusters are within budget
		double cost = this->problem_->getCost(*it) +
		              this->problem_->getCost(this->problem_->getSpecificItem());

		if (cost <= this->problem_->getbudget()) {
			std::set<int> *temp = new std::set<int>();
			temp->insert(*it);
			temp->insert(this->problem_->getSpecificItem());
			clustering[*it] = temp;
		}
	}

	// Merge iteratively
	bool merged = true;

	while(merged && clustering.size() > numToProduce) {
		merged = this->tryMerge(clustering);
	}

	if( merged == false ) {
		//TODO: hacer log
	}


	for (std::map<int, std::set<int>*>::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *snowflake = new SnowFlake(*it->second, this->problem_);
		std::set<int> ids = snowflake->ids();
		delete snowflake;
	}

	SnowFlakeVector* solution = new SnowFlakeVector;

	for (std::map<int, std::set<int>*>::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
		solution->push_back(*aFlake);
	}

	return solution;
}

bool RestrictedHACSWithSpecificItemSolver::tryMerge(std::map<int, std::set<int>*>& clustering)
{
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	double maxCompatibility = -1.00;

	for (std::map<int, std::set<int>*>::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		std::set<int> *cluster1 = it->second;

		for (std::map<int, std::set<int>*>::iterator it2 = it; it2 != clustering.end(); ++it2) {
			if (it == it2) {
				continue;
			}

			std::set<int> *cluster2 = it2->second;

			//check if these can be merged
			if (this->checkBudgetAndCoverageConstraint(*cluster1, *cluster2, this->problem_->getSpecificItem())) {
				// if they can be merged, measure their compatibility
				double compatibility = this->problem_->maxPairwiseCompatibility(*cluster1, *cluster2);

				if (compatibility > maxCompatibility) {
					bestC1 = it->first;
					bestC2 = it2->first;
					maxCompatibility = compatibility;
				}
			}
		}
	}

	if (bestC1 >= 0 && bestC2 >= 0) {
		//copy elements from c2 into c1
		std::set<int> *bestSetC1 = clustering.at(bestC1);
		std::set<int> *bestSetC2 = clustering.at(bestC2);
		bestSetC1->insert(bestSetC2->begin(), bestSetC2->end());

		//remove c2 from cluster
		clustering.erase(bestC2);
		return true;
	}

	else {
		return false;
	}
}
