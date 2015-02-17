/*
 * clusterAndPickSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "clusterAndPickSolver.h"
#include "../cluster/clustering.h"

ClusterAndPickSolver::~ClusterAndPickSolver() {
}

SnowFlakeVector* ClusterAndPickSolver::solve(int numSnowflakes){

	std::vector<int>* clustering;
	clustering = Clustering::symmetrizeAndCluster(*this->problem_->getCompat(), numSnowflakes);
	if (clustering->size()!= this->problem_->numNodes()) {
        //TODO: hacer log
	}

	std::set<int> clusterIds = std::set<int>();


	for (std::vector<int>::iterator clusterNum = clustering->begin(); clusterNum != clustering->end(); ++clusterNum) {
		clusterIds.insert(*clusterNum);
	}

	SnowFlakeVector* solution;
	solution = new SnowFlakeVector();
	for (std::set<int>::iterator clusterId = clusterIds.begin(); clusterId != clusterIds.end(); ++clusterId) {
		std::set<int> clusterMembers = std::set<int>();
		for (int node = 0; node < clustering->size(); ++node) {
			if ((*clustering)[node] == *clusterId) {
				clusterMembers.insert(node);
			}
		}

		SnowFlake *bestFlake = bestSnowFlake(clusterMembers);

		solution->push_back(*bestFlake);
	}
	return solution;
}

SnowFlake* ClusterAndPickSolver::bestSnowFlake(const std::set<int>& clusterMembers){
	double bestScore = -1.0;
	SnowFlake* bestSnowflake;

	for (std::set<int>::iterator center = clusterMembers.begin(); center != clusterMembers.end(); ++center) {
		SnowFlake* snowflake = this->pickFlake(*center, clusterMembers);
		double score = snowflake->getSumIntraCompat();
		if (score > bestScore) {
			bestScore = score;
			bestSnowflake = snowflake;
		}
		else{
			delete snowflake;
		}
	}

	return bestSnowflake;
}
