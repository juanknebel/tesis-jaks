#ifndef LOCALSEARCHSOLVER_H
#define LOCALSEARCHSOLVER_H

#include "../abstract/produceAndChooseSolver.h"

class GreedySolver : public ProduceAndChooseSolver {
public:
	GreedySolver(double interSimilarityWeight_, double budget) : ProduceAndChooseSolver(interSimilarityWeight_, budget) {
	}
	~GreedySolver() {}
	std::vector<SnowFlake> produceManySnowflakes(int numSnowflakes, ProblemInstance &theProblem);
	std::vector<SnowFlake> produceManySnowflakes1(int numSnowflakes, ProblemInstance &theProblem);
	std::vector<SnowFlake> produceManySnowflakes2(int numSnowflakes, ProblemInstance &theProblem);
};

#endif // LOCALSEARCHSOLVER_H
