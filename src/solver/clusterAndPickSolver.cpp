/*
 * clusterAndPickSolver.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: amit
 */

#include "clusterAndPickSolver.h"
#include "../cluster/clustering.h"
#include "../util/system/Logger.h"


ClusterAndPickSolver::~ClusterAndPickSolver() {
}

SnowFlakeVector* ClusterAndPickSolver::solve(int numSnowflakes){

	IntVector* clustering;
	clustering = Clustering::symmetrizeAndCluster(*this->problem_->getCompat(), numSnowflakes);
	if (clustering->size()!= this->problem_->numNodes()) {
        //TODO: hacer log
	}

	IntSet clusterIds = IntSet();


	for (IntVector::iterator clusterNum = clustering->begin(); clusterNum != clustering->end(); ++clusterNum) {
		clusterIds.insert(*clusterNum);
	}

	SnowFlakeVector* solution;
	solution = new SnowFlakeVector();
	for (IntSet::iterator clusterId = clusterIds.begin(); clusterId != clusterIds.end(); ++clusterId) {
		IntSet clusterMembers = IntSet();
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

SnowFlake* ClusterAndPickSolver::bestSnowFlake(const IntSet& clusterMembers){
	double bestScore = -1.0;
	SnowFlake* bestSnowflake;

	for (IntSet::iterator center = clusterMembers.begin(); center != clusterMembers.end(); ++center) {
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
