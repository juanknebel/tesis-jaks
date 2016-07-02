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
	MapIntIntSet clustering = MapIntIntSet();
	IntSet ids = this->problem_->getIds();

	for (IntSet::iterator it = ids.begin(); it != ids.end(); ++it) {
		// Make sure all singleton clusters are within budget
		double cost = this->problem_->getCost(*it) +
		              this->problem_->getCost(this->problem_->getSpecificItem());

		if (cost <= this->problem_->getbudget()) {
			IntSet *temp = new IntSet();
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


	for (MapIntIntSet::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *snowflake = new SnowFlake(*it->second, this->problem_);
		std::set<int> ids = snowflake->ids();
		delete snowflake;
	}

	SnowFlakeVector* solution = new SnowFlakeVector;

	for (MapIntIntSet::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
		solution->push_back(*aFlake);
	}

	return solution;
}

bool RestrictedHACSWithSpecificItemSolver::tryMerge(MapIntIntSet& clustering)
{
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	Double maxCompatibility = -1.00;

	for (MapIntIntSet::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		IntSet *cluster1 = it->second;

		for (MapIntIntSet::iterator it2 = it; it2 != clustering.end(); ++it2) {
			if (it == it2) {
				continue;
			}

			IntSet *cluster2 = it2->second;

			//check if these can be merged
			if (this->checkBudgetAndCoverageConstraint(*cluster1, *cluster2, this->problem_->getSpecificItem())) {
				// if they can be merged, measure their compatibility
				Double compatibility = this->problem_->maxPairwiseCompatibility(*cluster1, *cluster2);

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
		IntSet *bestSetC1 = clustering.at(bestC1);
		IntSet *bestSetC2 = clustering.at(bestC2);
		bestSetC1->insert(bestSetC2->begin(), bestSetC2->end());

		//remove c2 from cluster
		clustering.erase(bestC2);
		return true;
	}

	else {
		return false;
	}
}
