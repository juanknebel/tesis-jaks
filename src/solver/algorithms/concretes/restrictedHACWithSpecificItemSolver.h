/*
 * RestrictedHACSWithSpecificItemSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSWITHSPECIFICITEMSOLVER_H_
#define RESTRICTEDHACSWITHSPECIFICITEMSOLVER_H_

#include "../abstract/multiplicativeEffortProduceAndChooseSolver.h"

class RestrictedHACSWithSpecificItemSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSWithSpecificItemSolver(double interSimilarityWeight_, double budget) :  MultiplicativeEffortProduceAndChooseSolver(interSimilarityWeight_, budget) {

	}
	virtual ~RestrictedHACSWithSpecificItemSolver();

	std::vector<SnowFlake> produceManySnowflakes(int numToProduce, ProblemInstance &theProblem);
protected:
	bool tryMerge(std::map<int, std::set<Flake> > &clustering, ProblemInstance &theProblem);
};

#endif /* RESTRICTEDHACSOLVER_H_ */
