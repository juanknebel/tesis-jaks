/*
 * produceAndChooseSolver.cpp
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#include "produceAndChooseSolver.h"
#include <float.h>

void ProduceAndChooseSolver::setRankingStrategy(ProduceAndChooseSolver::RankingStrategy strategy) {
	this->rankingStrategy_ = strategy;
}

ProduceAndChooseSolver::~ProduceAndChooseSolver() {

}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getRankingStrategy() {
	return this->rankingStrategy_;
}

void ProduceAndChooseSolver::setInterSimilarityWeight(Double interSimilarityWeight) {
	if (this->rankingStrategy_ == RANK_BY_INTRA_INTER || this->rankingStrategy_ == RANK_BY_DENSEST_SUBGRAPH) {
		this->interSimilarityWeight_ = interSimilarityWeight_;
	}
	else {
		//ARROJAR EXCEPCION This ranking strategy does not need an inter-similarity weight
	}
}

SnowFlakeVector* ProduceAndChooseSolver::solve(int numSnowFlakes) {
	SnowFlakeVector* produced = this->produceManySnowflakes(this->numToProduce(numSnowFlakes));
	produced = this->getTopSolutionByRankingStrategy(produced, numSnowFlakes);
	return produced;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionByRankingStrategy(SnowFlakeVector* produced, int numRequested ) {
	SnowFlakeVector* ret;
	switch (this->rankingStrategy_) {
		case ProduceAndChooseSolver::RANK_BY_INTRA:
			ret = this->getTopSolutionsByIntra(produced,numRequested);
			break;
		case ProduceAndChooseSolver::RANK_BY_INTRA_INTER:
			if (this->interSimilarityWeight_ < 0.0) {
				//throw new IllegalArgumentException("This ranking strategy requires an inter similarity weight");
			}
			ret = this->getTopSolutionsByInterIntra(produced, numRequested);
			break;
		case ProduceAndChooseSolver::RANK_BY_DENSEST_SUBGRAPH:
			if (this->interSimilarityWeight_ < 0.0) {
				//throw new IllegalArgumentException("This ranking strategy requires an inter similarity weight");
			}
			ret = this->getTopSolutionsByDensestSubgraph(produced, numRequested);
			break;
		default:
			break;
	}
	return ret;
}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getDefault() {
	return RANK_BY_INTRA;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByIntra(SnowFlakeVector* produced, int numRequested) {
	SnowFlake::sortByDecresingSumCompat(*produced);
	int minValue = ((numRequested < produced->size()) ? numRequested : produced->size());
	SnowFlakeVector* selected = new SnowFlakeVector(produced->begin(), produced->begin() + minValue);
	return selected;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByInterIntra(SnowFlakeVector* produced, int numRequested){
	if(this->interSimilarityWeight_ < 0.00) {
		//ARROJAR EXCEPCION "You need to set the value of 'inter similarity weight'"
	}
	SnowFlake::sortByDecresingSumCompat(*produced);
	SnowFlakeVector available(*produced);
	SnowFlakeVector *selected = new SnowFlakeVector(numRequested);
	Double currentSumIntra = 0.0;
	Double currentSumOneMinusInter = 0.0;
	while (selected->size() < numRequested && selected->size() < produced->size()) {
		Double maxScore = FLT_MIN;
		int bestCandidateId = -1;
		if (available.size() == 0) {
			//ARROJAR EXCPECION "There are no available condidates
		}
		for (Uint candidateId = 0; candidateId < available.size(); ++candidateId) {
			SnowFlake candidate = available[candidateId];
			Double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter);
			if (score > maxScore) {
				bestCandidateId = candidateId;
			}
		}

		if (bestCandidateId == -1) {
			//ARROJAR EXCEPCION "There is no best candidate (available.size()==" + available.size() + ", maxScore==" + maxScore + ")"
		}

		//Calcula las nuevas puntuaciones
		SnowFlake bestCandidate = available[bestCandidateId];
		currentSumIntra += bestCandidate.getSumIntraCompat();
		for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
			currentSumOneMinusInter += 1.0 - problem_->maxPairwiseCompatibility((*it).ids(), bestCandidate.ids());
		}

		//Borro el candidato que ya use
		available.erase(available.begin() + bestCandidateId);
		//Agrego el elemento a la solucion
		selected->push_back(bestCandidate);
	}
	return selected;
}

Double ProduceAndChooseSolver::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter) {
	Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
	Double sumOneMinusInter = selectedSumOneMinusInter;
	for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
		sumOneMinusInter += 1.0 - this->problem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
	}
	return ((1.0 - interSimilarityWeight_) * sumIntra) + (interSimilarityWeight_ * sumOneMinusInter);
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByDensestSubgraph(SnowFlakeVector* produced, int numRequested) {
	int numProduced = produced->size();
	Double gamma = 1.0 - this->interSimilarityWeight_;
	MatrixWrapper* w;
	w= new MatrixConcrete(numProduced, numProduced);

	for (int ui = 0; ui < numProduced; ++ui) {
		SnowFlake& u = (*produced)[ui];
		for (int vi = 0; vi < numProduced; ++vi) {
			SnowFlake& v = (*produced)[vi];
			Double val = ((gamma / (2.0 * ((Double) numRequested - 1.0))) * (u.getSumIntraCompat() + v.getSumIntraCompat()))
					+ (1.0 - gamma) * (1.0 - this->problem_->maxPairwiseCompatibility(u.ids(), v.ids()));
			w->set(ui,vi,val);
		}
	}

	IntSet selected = IntSet();
	for (int ui = 0; ui < numProduced; ui++) {
			selected.insert(ui);
	}

	while(selected.size() > numRequested){
		Double minWeightedDegree = FLT_MAX;
		int minElement = -1;
		for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
			Double weightedDegree = 0.0;
			for (IntSet::iterator vi = selected.begin(); vi != selected.end(); ++vi) {
				weightedDegree += w->get(*ui,*vi);
				if (weightedDegree > minWeightedDegree) {
					break;
				}
			}
			if (weightedDegree < minWeightedDegree) {
				minWeightedDegree = weightedDegree;
				minElement = *ui;
			}
		}
		if (selected.count(minElement) == 0) {
			//ARROJAR EXCEPCION "Tried to remove element " + minElement + " that does not belong to " + selected
		}
		selected.erase(minElement);
	}
	SnowFlakeVector* solution = new SnowFlakeVector[numRequested];
	int i = 0;
	for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
		solution[i] = produced[*ui];
	}
	return solution;
}
