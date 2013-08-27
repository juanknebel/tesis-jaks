/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"

RestrictedHACSolver::~RestrictedHACSolver() {
	// TODO Auto-generated destructor stub
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes(int numToProduce) {
	if (this->problem_->numNodes() < numToProduce) {
		//ARROJAR EXCEPCION Too few nodes
	}
	// Put each item in its own cluster
	Int2ObjectOpenHashMap clustering = Int2ObjectOpenHashMap();
	IntSet ids = this->problem_->getIds();
	for (IntSet::iterator it = ids.begin(); it != ids.end(); ++it) {
		// Make sure all singleton clusters are within budget
		if (this->problem_->getCost(*it) <= this->problem_->getbudget()) {
			IntSet temp = IntSet();
			temp.insert(*it);
			clustering[*it] = temp;
		}
	}
	// Merge iteratively
	bool merged = true;
	while(merged && clustering.size() > numToProduce) {
		merged = tryMerge(clustering);
	}

	if( merged == false ) {
		//not merged
	}
	SnowFlakeVector* solution = new SnowFlakeVector;
	for (Int2ObjectOpenHashMap::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(it->second, this->problem_);
		solution->push_back(*aFlake);
	}

	return solution;
}

bool RestrictedHACSolver::tryMerge(Int2ObjectOpenHashMap& clustering) {
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	Double maxCompatibility = -1.00;
	for (Int2ObjectOpenHashMap::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		IntSet cluster1 = it->second;
		for (Int2ObjectOpenHashMap::iterator it2 = it; it != clustering.end(); ++it2) {
			if (it == it2) {
				continue;
			}
			IntSet cluster2 = it2->second;
			//check if these can be merged
			if (this->checkBudgetAndCoverageConstraint(cluster1, cluster2)) {
				// if they can be merged, measure their compatibility
				Double compatibility = this->problem_->maxPairwiseCompatibility(cluster1, cluster2);
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

		//remove c2 from cluster
		return true;
	}
	else {
		return false;
	}
}
