/*
 * RestrictedHACSWithSpecificItemSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACWithSpecificItemSolver.h"
#include "../../../problem/factoryFlake.h"

RestrictedHACSWithSpecificItemSolver::~RestrictedHACSWithSpecificItemSolver()
{
	// TODO Auto-generated destructor stub
}

std::vector<SnowFlake> RestrictedHACSWithSpecificItemSolver::produceManySnowflakes(int numToProduce, ProblemInstance &theProblem)
{
	if (theProblem.numNodes() < numToProduce) {
		throw Exception(__FILE__, __LINE__, "Too few nodes");
	}

	// Put each item with specific item in its own cluster
	std::map<int, std::set<Flake>> clustering = std::map<int, std::set<Flake>>();
	std::set<Flake> allFlakes = FactoryFlake::createAllFlakes(theProblem);

	for (auto aFlake : allFlakes) {
		// Make sure all singleton clusters are within budget
		double cost = aFlake.getCost() + this->specificItem_.getCost();

		if (cost <= this->budget_) {
			std::set<Flake> temp = std::set<Flake> ();
			temp.insert(aFlake);
			temp.insert(this->specificItem_);
			clustering[aFlake.getId()] = temp;
		}
	}

	// Merge iteratively
	bool merged = true;

	while(merged && clustering.size() > numToProduce) {
		merged = this->tryMerge(clustering, theProblem);
	}

	if(!merged) {
		//TODO: hacer log
	}

	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (auto aSetOfFlakes : clustering) {
		SnowFlake aFlake = SnowFlake(aSetOfFlakes.second);
		solution.push_back(aFlake);
	}

	return solution;
}

bool RestrictedHACSWithSpecificItemSolver::tryMerge(std::map<int, std::set<Flake> > &clustering, ProblemInstance &theProblem)
{
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	double maxCompatibility = -1.00;

	for (auto aMapIntSetFlakeIt = clustering.begin(); aMapIntSetFlakeIt != clustering.end(); ++aMapIntSetFlakeIt) {
		std::set<Flake> cluster1 = aMapIntSetFlakeIt->second;
		for (auto otherMapIntSetFlakeIt = aMapIntSetFlakeIt; otherMapIntSetFlakeIt != clustering.end(); ++otherMapIntSetFlakeIt) {
			if (aMapIntSetFlakeIt == otherMapIntSetFlakeIt) {
				continue;
			}
			std::set<Flake> cluster2 = otherMapIntSetFlakeIt->second;
			bool canAdd = this->checkBudgetAndCoverageConstraint(cluster1, cluster2, theProblem);
			if (canAdd) {
				double compatibility = SnowFlake::maxPairwiseCompatibility(cluster1, cluster2, theProblem);
				if (compatibility > maxCompatibility) {
					bestC1 = aMapIntSetFlakeIt->first;
					bestC2 = otherMapIntSetFlakeIt->first;
					maxCompatibility = compatibility;
				}
			}
		}
	}

	if (bestC1 >= 0 && bestC2 >= 0) {
		//copy elements from c2 into c1
		std::set<Flake> bestSetC1 = clustering.at(bestC1);
		std::set<Flake> bestSetC2 = clustering.at(bestC2);
		bestSetC1.insert(bestSetC2.begin(), bestSetC2.end());

		//remove c2 from cluster
		clustering.erase(bestC2);
		return true;
	}

	else {
		return false;
	}
}
