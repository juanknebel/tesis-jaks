/*
 * snowflakesOneByOneSolver.h
 *
 *  Created on: Aug 12, 2013
 *      Author: amit
 */

#ifndef SNOWFLAKESONEBYONESOLVER_H_
#define SNOWFLAKESONEBYONESOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class SnowflakesOneByOneSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	static bool SNOWFLAKE_MEMBERS_CAN_BE_PIVOTS;

	SnowflakesOneByOneSolver(double interSimilarityWeight_, double budget) : MultiplicativeEffortProduceAndChooseSolver (interSimilarityWeight_, budget) {
	}
	~SnowflakesOneByOneSolver() {};

protected:
	std::vector<SnowFlake> produceManySnowflakes(int numSnowflakes, ProblemInstance &theProblem);
	virtual Flake getPivot(std::set<Flake>& pivotsUsed, std::set<Flake>& possiblePivots, ProblemInstance& theProblem) = 0;
	virtual bool candidateAcceptable(SnowFlake &candidate, ProblemInstance &theProblem);

private:
	std::vector<SnowFlake> produceManySnowflakesSimple(int numSnowflakes, ProblemInstance &theProblem);
	std::vector<SnowFlake> produceManySnowflakesWithSpecificItem(int numSnowflakes, ProblemInstance &theProblem);
};

#endif /* SNOWFLAKESONEBYONESOLVER_H_ */
