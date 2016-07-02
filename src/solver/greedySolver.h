#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "produceAndChooseSolver.h"

class GreedySolver : public ProduceAndChooseSolver {
public:
	GreedySolver(ProblemInstance* problem) : ProduceAndChooseSolver(problem) {
	}
	~GreedySolver() {}
	SnowFlakeVector* produceManySnowflakes(int numSnowflakes);
	SnowFlakeVector* produceManySnowflakes1(int numSnowflakes);
	SnowFlakeVector* produceManySnowflakes2(int numSnowflakes);
	int numToProduce(int numRequested);
};

#endif // LOCALSEARCHSOLVER_H
