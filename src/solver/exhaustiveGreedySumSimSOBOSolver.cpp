/*
 * exhaustiveGreedySumSimSOBOSolver.cpp
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#include "exhaustiveGreedySumSimSOBOSolver.h"

SnowFlake ExhaustiveGreedySumSimSOBOSolver::pickFlake(int pivot, const std::set<int>& clusterMembers)
{
	int n = clusterMembers.size();
	std::set<int> membersSortedSelected;
	std::vector<int> membersUnsorted (clusterMembers.begin(), clusterMembers.end());
	std::vector<int> membersSorted(n, -1);
	int mostSimilarElement, elem, elem2;
	double mostSimilarElementSumSimilarity, sumSimilarity;

	for(int i = 0; i < n; ++i) {
		mostSimilarElement = -1;
		mostSimilarElementSumSimilarity = -1.00;

		// Choose which element has a larger sum of similarities to the partial bundle
		for (int j = 0; j < n; ++j) {
			elem = membersUnsorted[j];

			if (membersSortedSelected.count(elem) ==  0) {
				// Add distance to pivot
				sumSimilarity = this->problem_->getCompat(pivot, elem);

				// First check if it is closest to the pivot
				// Add distance to elements already in the bundle
				for( int k=0; k<i; k++ ) {
					int elem2 = membersSorted[k];
					sumSimilarity += this->problem_->getCompat(elem2, elem);
				}

				if( sumSimilarity > mostSimilarElementSumSimilarity ) {
					mostSimilarElement = elem;
					mostSimilarElementSumSimilarity = sumSimilarity;
				}
			}
		}

		// Add selected element
		if (mostSimilarElement == -1) {
			throw Exception(__FILE__, __LINE__, "Did not find an element to select");
		}

		membersSortedSelected.insert(mostSimilarElement);
		membersSorted[i] = mostSimilarElement;
	}

	return this->pickFlakeGivenPermutation(pivot, membersSorted);
}
