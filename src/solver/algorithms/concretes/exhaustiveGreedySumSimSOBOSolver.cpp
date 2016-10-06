/*
 * exhaustiveGreedySumSimSOBOSolver.cpp
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#include "exhaustiveGreedySumSimSOBOSolver.h"

SnowFlake ExhaustiveGreedySumSimSOBOSolver::pickFlake(Flake pivot, const std::set<Flake>& clusterMembers, ProblemInstance& theProblem)
{
	int n = clusterMembers.size();
	std::set<Flake> membersSortedSelected;
	std::vector<Flake> membersUnsorted (clusterMembers.begin(), clusterMembers.end());
	std::vector<Flake> membersSorted(n, Flake());
	Flake mostSimilarElement, elem, elem2;
	double mostSimilarElementSumSimilarity, sumSimilarity;

	for(int i = 0; i < n; ++i) {
		mostSimilarElement = Flake();
		mostSimilarElementSumSimilarity = -1.00;

		// Choose which element has a larger sum of similarities to the partial bundle
		for (int j = 0; j < n; ++j) {
			elem = membersUnsorted[j];

			if (membersSortedSelected.count(elem) ==  0) {
				// Add distance to pivot
				sumSimilarity = Flake::getCompat(pivot, elem, theProblem);

				// First check if it is closest to the pivot
				// Add distance to elements already in the bundle
				for( int k=0; k<i; k++ ) {
					Flake elem2 = membersSorted[k];
					sumSimilarity += Flake::getCompat(elem2, elem, theProblem);
				}

				if( sumSimilarity > mostSimilarElementSumSimilarity ) {
					mostSimilarElement = elem;
					mostSimilarElementSumSimilarity = sumSimilarity;
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
