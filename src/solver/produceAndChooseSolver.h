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
			/**
			* Sort in decreasing order by intra similarity, then pick the top elements.
			*/
			RANK_BY_INTRA = 0,
			/**
			* Apply a greedy heuristic to add the element that increases the most ( gamma * intra + ( 1
			* - gamma ) * inter )
			*/
			RANK_BY_INTRA_INTER,
			/**
			* Apply a densest-subgraph heuristic.
			*/
            RANK_BY_DENSEST_SUBGRAPH,
            /**
            * Hace lo mismo que el INTRA_INTER pero genera tuplas para la seleccion
            */
            RANK_BY_INTRA_INTER_TUPLE,
            /**
             * Aplica una seleccion similiar al RANK_BY_INTRA_INTER pero compensa la primer parte
             */
            RANK_BY_INTRA_INTER_PROPORTIONAL
		};

	ProduceAndChooseSolver(ProblemInstance* problem) : Solver(problem) {
		this->rankingStrategy_ = ProduceAndChooseSolver::getDefault();
		this->interSimilarityWeight_ = 0.0;
	}
	~ProduceAndChooseSolver() {};

	void setRankingStrategy(ProduceAndChooseSolver::RankingStrategy strategy);
	ProduceAndChooseSolver::RankingStrategy getRankingStrategy();
	void setInterSimilarityWeight(Double interSimilarityWeight);
	SnowFlakeVector* solve(int numSnowFlakes);
	SnowFlakeVector* getTopSolutionByRankingStrategy(SnowFlakeVector* produced, int numRequested );
	virtual int numToProduce(int numRequested) = 0;

protected:
	RankingStrategy rankingStrategy_;
	/**
	* To be used with {@link RankingStrategy#RANK_BY_INTRA_INTER}
	*/
	Double interSimilarityWeight_;
	static ProduceAndChooseSolver::RankingStrategy getDefault();
	SnowFlakeVector* getTopSolutionsByIntra(SnowFlakeVector* produced, int numRequested);
	SnowFlakeVector* getTopSolutionsByInterIntra(SnowFlakeVector* produced, int numRequested);
    SnowFlakeVector* getTopSolutionsByInterIntraByTuples(SnowFlakeVector* produced, int numRequested);
    SnowFlakeVector* getTopSolutionsByIntraInterProportional(SnowFlakeVector* produced, int numRequested);

	/**
	* Score a set of snowflakes composed of all the elements in 'selected' plus the element
	* 'candidate'.
	*
	* The score is {@link #interSimilarityWeight} * sum(inter) + ( 1 -
	* {@link #interSimilarityWeight}) * sum(intra)
	*
	* Used by {@link #getTopSolutionsByInterIntra(Vector, int)}.
	*
	* @param selected the snowflakes selected so far
	* @param candidate the new snowflake to add
	* @param selectedSumIntra the sum of {@link Snowflake#getSumIntraCompat()} for elements in
	*            selected
	* @return the score of the union
	*/
	Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter);
    Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, Double selectedSumIntra, Double selectedSumOneMinusInter);
    Double scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter, Double alpha, Double beta);

	/**
	*
	* Applies a heuristic to find a densest subgraph.
	*
	* The weights in the subgraph are a function of inter similarity and intra similarity.
	*
	* Y. Asahiro, K. Iwama, H. Tamaki, and T. Tokuyama. Greedily finding a dense subgraph. Journal
	* of Algorithms, 34(2):203 – 221, 2000.
	*
	* @param produced
	* @param numRequested
	* @return
	*/
	SnowFlakeVector* getTopSolutionsByDensestSubgraph(SnowFlakeVector* produced, int numRequested);

	/**
	* Generate a number of snowflakes
	*
	* @param numSnowflakes the minimum number of snowflakes to produce
	* @return a set of snowflakes, possibly larger than the number of requested elements
	*/
	virtual SnowFlakeVector* produceManySnowflakes(int numSnowflakes) = 0;
};


#endif /* PRODUCEANDCHOOSESOLVER_H_ */
