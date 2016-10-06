/*
 * exhaustiveGreedyAnySimSOBOSolver.cpp
 *
 *  Created on: 14/08/2013
 *      Author: zero
 */

#include "exhaustiveGreedyAnySimSOBOSolver.h"

SnowFlake ExhaustiveGreedyAnySimSOBOSolver::pickFlake(Flake pivot, const std::set<Flake> &clusterMembers, ProblemInstance& theProblem)
{
	int n = clusterMembers.size();
	std::set<Flake> membersSortedSelected;
	std::vector<Flake> membersUnsorted (clusterMembers.begin(), clusterMembers.end());
	std::vector<Flake> membersSorted(n, Flake());
	Flake mostSimilarElement, elem, elem2;
	double mostSimilarElementSimilarity;

	for(int i = 0; i < n; ++i) {
		mostSimilarElement = Flake();
		mostSimilarElementSimilarity = -1.00;

		// Choose which element has a larger similarity to any element in the partial bundle
		for (int j = 0; j < n; ++j) {
			elem = membersUnsorted[j];

			if (membersSortedSelected.count(elem) ==  0) {
				// First check if it is closest to the pivot
				if (Flake::getCompat(pivot, elem, theProblem) > mostSimilarElementSimilarity) {
					mostSimilarElement = elem;
					mostSimilarElementSimilarity = Flake::getCompat(pivot, elem, theProblem);
				}

				// Then check if it is closest to any element
				for( int k=0; k<i; k++ ) {
					elem2 = membersSorted[k];

					if (Flake::getCompat(elem2, elem, theProblem) > mostSimilarElementSimilarity) {
						mostSimilarElement = elem;
						mostSimilarElementSimilarity = Flake::getCompat(elem2, elem, theProblem);
					}
				}
			}
		}

		// Add selected element
		if (mostSimilarElement == Flake()) {
			throw Exception(__FILE__, __LINE__, "Did not find an element to select");
		}

		membersSortedSelected.insert(mostSimilarElement);
		membersSorted[i] = mostSimilarElement;
	}

	return this->pickFlakeGivenPermutation(pivot, membersSorted, theProblem);
}
