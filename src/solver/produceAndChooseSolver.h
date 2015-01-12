/*
 * produceAndChooseSolver.h
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#ifndef PRODUCEANDCHOOSESOLVER_H_
#define PRODUCEANDCHOOSESOLVER_H_

#include "solver.h"
#include "selector/selector.h"

class ProduceAndChooseSolver : public Solver {
public:
	ProduceAndChooseSolver(ProblemInstance* problem, Selector* selector) : Solver(problem, selector) {
        this->selectorStrategy_ = ProduceAndChooseSolver::getDefault();
		this->interSimilarityWeight_ = 0.0;
	}
    ~ProduceAndChooseSolver() {}

    Selector* getSelector();
	void setInterSimilarityWeight(Double interSimilarityWeight);
	SnowFlakeVector* solve(int numSnowFlakes);
    SnowFlakeVector* getTopSolutionByRankingStrategy(SnowFlakeVector* produced, int numRequested);
	virtual int numToProduce(int numRequested) = 0;

protected:
    Selector* selectorStrategy_;
	Double interSimilarityWeight_;
    static Selector* getDefault();
	virtual SnowFlakeVector* produceManySnowflakes(int numSnowflakes) = 0;
};

#endif /* PRODUCEANDCHOOSESOLVER_H_ */
