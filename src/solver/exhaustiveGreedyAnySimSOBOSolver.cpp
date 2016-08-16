/*
 * exhaustiveGreedyAnySimSOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#include "exhaustiveGreedyAnySimSOBOSolver.h"

SnowFlake ExhaustiveGreedyAnySimSOBOSolver::pickFlake(int pivot, const IntSet& clusterMembers)
{
	Uint n = clusterMembers.size();
	IntSet membersSortedSelected;
	IntVector membersUnsorted (clusterMembers.begin(), clusterMembers.end());
	IntVector membersSorted(n, -1);
	int mostSimilarElement, elem, elem2;
	Double mostSimilarElementSimilarity;

	for(Uint i = 0; i < n; ++i) {
		mostSimilarElement = -1;
		mostSimilarElementSimilarity = -1.00;

		// Choose which element has a larger similarity to any element in the partial bundle
		for (Uint j = 0; j < n; ++j) {
			elem = membersUnsorted[j];

			if (membersSortedSelected.count(elem) ==  0) {
				// First check if it is closest to the pivot
				if (this->problem_->getCompat(pivot, elem) > mostSimilarElementSimilarity) {
					mostSimilarElement = elem;
					mostSimilarElementSimilarity = this->problem_->getCompat(pivot, elem);
				}

				// Then check if it is closest to any element
				for( Uint k=0; k<i; k++ ) {
					elem2 = membersSorted[k];

					if (this->problem_->getCompat(elem2, elem) > mostSimilarElementSimilarity) {
						mostSimilarElement = elem;
						mostSimilarElementSimilarity = this->problem_->getCompat(elem2, elem);
					}
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
