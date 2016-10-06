/*
 * produceAndChooseSolver.h
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#ifndef PRODUCEANDCHOOSESOLVER_H_
#define PRODUCEANDCHOOSESOLVER_H_

#include "solver.h"

class ProduceAndChooseSolver : public Solver {
public:
	enum RankingStrategy {
	    RANK_BY_INTRA = 0, RANK_BY_INTRA_INTER, RANK_BY_DENSEST_SUBGRAPH, RANK_BY_INTRA_INTER_TUPLE, RANK_BY_INTRA_INTER_PROPORTIONAL
	};

	ProduceAndChooseSolver(double interSimilarityWeight_, double budget) : Solver(interSimilarityWeight_, budget) {
		this->rankingStrategy_ = ProduceAndChooseSolver::getDefault();
		this->interSimilarityWeight_ = 0.0;
	}
	~ProduceAndChooseSolver() {};

	void setRankingStrategy(ProduceAndChooseSolver::RankingStrategy strategy);
	ProduceAndChooseSolver::RankingStrategy getRankingStrategy();

protected:
	std::vector<SnowFlake> solve(ProblemInstance& theProblem, int numSnowFlakes);
	std::vector<SnowFlake>
	getTopSolutionByRankingStrategy(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem);
	RankingStrategy rankingStrategy_;
	static ProduceAndChooseSolver::RankingStrategy getDefault();
	std::vector<SnowFlake>
	getTopSolutionsByIntra(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem);
	std::vector<SnowFlake>
	getTopSolutionsByInterIntra(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem);
	std::vector<SnowFlake> getTopSolutionsByInterIntraByTuples(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem);
	std::vector<SnowFlake> getTopSolutionsByIntraInterProportional(std::vector<SnowFlake> &produced, int numRequested,
                                                                       ProblemInstance &theProblem);
	double scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                  double selectedSumOneMinusInter, ProblemInstance &theProblem);
	double scoreSetIntraInterWithSpecificProfile(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                                     double selectedSumOneMinusInter, ProblemInstance &theProblem);
	double scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, SnowFlake &candidateTwo,
                                  double selectedSumIntra, double selectedSumOneMinusInter, ProblemInstance &theProblem);
	double scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                  double selectedSumOneMinusInter, double alpha, double beta, ProblemInstance &theProblem);
	std::vector<SnowFlake>
    getTopSolutionsByDensestSubgraph(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem);
	virtual std::vector<SnowFlake> produceManySnowflakes(int numSnowflakes, ProblemInstance &theProblem) = 0;
};


#endif /* PRODUCEANDCHOOSESOLVER_H_ */
