/*
 * clusterAndPickSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "clusterAndPickSolver.h"
#include "../../../cluster/clustering.h"
#include "../../../problem/factoryFlake.h"

ClusterAndPickSolver::~ClusterAndPickSolver()
{
}

std::vector<SnowFlake> ClusterAndPickSolver::solve(ProblemInstance& theProblem, int numSnowFlakes)
{
	std::vector<int> *clusteringId = Clustering::symmetrizeAndCluster(*theProblem.getCompat(), numSnowFlakes);

	std::vector<Flake> clustering;
	for (auto flakeId : *clusteringId) {
        Flake newFlake = FactoryFlake::createNewFlake(flakeId, theProblem);
        clustering.push_back(newFlake);
	}

	if (clustering.size()!= theProblem.numNodes()) {
		//TODO: hacer log
	}

	std::set<Flake> clusterIds = std::set<Flake>();


	for (auto clusterNum : clustering) {
		clusterIds.insert(clusterNum);
	}

	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (auto clusterId : clusterIds) {
		std::set<Flake> clusterMembers = std::set<Flake>();
		for (auto aFlake : clustering) {
			if (aFlake == clusterId) {
				clusterMembers.insert(aFlake);
			}
		}

		SnowFlake bestFlake = bestSnowFlake(clusterMembers, theProblem);

		solution.push_back(bestFlake);
	}

	return solution;
}

SnowFlake ClusterAndPickSolver::bestSnowFlake(const std::set<Flake>& clusterMembers, ProblemInstance& theProblem)
{
	double bestScore = -1.0;
	SnowFlake bestSnowflake;

	for (auto aFlake : clusterMembers) {
		SnowFlake snowflake = this->pickFlake(aFlake, clusterMembers, theProblem);
		double score = SnowFlake::getSumIntraCompat(snowflake, theProblem);

		if (score > bestScore) {
			bestScore = score;
			bestSnowflake = snowflake;
		}
	}
	return bestSnowflake;
}
