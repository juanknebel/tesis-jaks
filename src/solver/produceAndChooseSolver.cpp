/*
 * produceAndChooseSolver.cpp
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#include "produceAndChooseSolver.h"
#include "../util/system/stringUtilities.h"
#include "../util/logger/logger.h"
#include <float.h>
#include "../util/algorithm/localSearchBundles.h"

void ProduceAndChooseSolver::setRankingStrategy(ProduceAndChooseSolver::RankingStrategy strategy)
{
	this->rankingStrategy_ = strategy;
}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getRankingStrategy()
{
	return this->rankingStrategy_;
}

void ProduceAndChooseSolver::setInterSimilarityWeight(Double interSimilarityWeight)
{
	if (this->rankingStrategy_ == RANK_BY_INTRA_INTER || this->rankingStrategy_ == RANK_BY_DENSEST_SUBGRAPH
	        || this->rankingStrategy_ == RANK_BY_INTRA_INTER_TUPLE || this->rankingStrategy_ == RANK_BY_INTRA_INTER_PROPORTIONAL) {
		this->interSimilarityWeight_ = interSimilarityWeight;
	}

	else {
		throw Exception(__FILE__, __LINE__, "This ranking strategy does not need an inter-similarity weight");
	}
}

SnowFlakeVector* ProduceAndChooseSolver::solve(int numSnowFlakes)
{
	SnowFlakeVector* produced = this->produceManySnowflakes(this->numToProduce(numSnowFlakes));
	SnowFlake::sortByDecresingSumCompat(*produced);
	produced = this->getTopSolutionByRankingStrategy(produced, numSnowFlakes);
	return produced;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionByRankingStrategy(SnowFlakeVector* produced, int numRequested )
{
	SnowFlakeVector* ret;

	switch (this->rankingStrategy_) {
	case ProduceAndChooseSolver::RANK_BY_INTRA:
		ret = this->getTopSolutionsByIntra(produced,numRequested);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByInterIntra(produced, numRequested);
		break;

	case ProduceAndChooseSolver::RANK_BY_DENSEST_SUBGRAPH:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByDensestSubgraph(produced, numRequested);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER_TUPLE:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByInterIntraByTuples(produced, numRequested);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER_PROPORTIONAL:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByIntraInterProportional(produced, numRequested);
		break;

	default:
		break;
	}

	produced->clear();
	delete produced;
	return ret;
}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getDefault()
{
	return RANK_BY_INTRA;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByIntra(SnowFlakeVector* produced, int numRequested)
{
	SnowFlake::sortByDecresingSumCompat(*produced);
	auto minValue = ((numRequested < produced->size()) ? numRequested : produced->size());
	SnowFlakeVector* selected = new SnowFlakeVector();

	for (int i = 0; i < minValue; ++i) {
		SnowFlake selectedSnowFlake(produced->at(i));
		selected->push_back(selectedSnowFlake);
	}

	return selected;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByInterIntra(SnowFlakeVector* produced, int numRequested)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	//SnowFlake::sortByDecresingSumCompat(*produced);
	SnowFlakeVector remainingFlakes(*produced);
	SnowFlakeVector *selected = new SnowFlakeVector();
	Double currentSumIntra = 0.0;
	Double currentSumOneMinusInter = 0.0;

	while (selected->size() < numRequested && selected->size() < produced->size()) {
		Double maxScore = -1.0;
		int bestCandidateId = -1;

		if (remainingFlakes.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no remainingFlakes condidates");
		}

		for (Uint candidateId = 0; candidateId < remainingFlakes.size(); ++candidateId) {
			SnowFlake candidate = remainingFlakes[candidateId];
			Double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter);

			//Double score = scoreSetIntraInterWithSpecificProfile(selected, candidate, currentSumIntra, currentSumOneMinusInter);
			if (score > maxScore) {
				bestCandidateId = candidateId;
				maxScore = score;
			}
		}

		if (bestCandidateId == -1) {
			throw Exception(__FILE__, __LINE__, "There is no best candidate (remainingFlakes.size()==" + convertToString(static_cast<int> (remainingFlakes.size()))
			                + ", maxScore==" + convertToString(maxScore) + ")");
		}

		//Calcula las nuevas puntuaciones
		SnowFlake bestCandidate = remainingFlakes[bestCandidateId];
		currentSumIntra += bestCandidate.getSumIntraCompat();

		for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
			currentSumOneMinusInter += 1.0 - problem_->maxPairwiseCompatibility((*it).ids(), bestCandidate.ids());
		}

		//Borro el candidato que ya use
		remainingFlakes.erase(remainingFlakes.begin() + bestCandidateId);
		//Agrego el elemento a la solucion
		selected->push_back(bestCandidate);
	}

	LocalSearchBundles localSearchBundles;
	SnowFlakeVector theFlakes = localSearchBundles.execute(1000,*selected, remainingFlakes, *this->problem_, this->interSimilarityWeight_);
	selected->clear();
	*selected = theFlakes;
	return selected;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByInterIntraByTuples(SnowFlakeVector* produced, int numRequested)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	SnowFlake::sortByDecresingSumCompat(*produced);
	SnowFlakeVector available(*produced);
	Uint sizeOfBundles = produced->size();
	bool *canUseSnowFlake = new bool[sizeOfBundles];

	for (Uint i = 0; i < sizeOfBundles; ++i) {
		canUseSnowFlake[i] = true;
	}

	SnowFlakeVector *selected = new SnowFlakeVector();
	Double currentSumIntra = 0.0;
	Double currentSumOneMinusInter = 0.0;

	while (selected->size() < numRequested && selected->size() < produced->size()) {
		Double maxScore = -1.0;
		int bestCandidateId = -1;
		int bestCandidateIdTwo = -1;

		if (available.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no available condidates");
		}

		for (Uint candidateId = 0; candidateId < sizeOfBundles; ++candidateId) {
			for (Uint candidateIdTwo = candidateId + 1; candidateIdTwo < sizeOfBundles; ++candidateIdTwo) {
				if (canUseSnowFlake[candidateId] && canUseSnowFlake[candidateIdTwo]) {
					SnowFlake candidate = available[candidateId];
					SnowFlake candidateTwo = available[candidateIdTwo];
					Double score = scoreSetIntraInter(selected, candidate, candidateTwo, currentSumIntra, currentSumOneMinusInter);

					if (score > maxScore) {
						bestCandidateId = candidateId;
						bestCandidateIdTwo = candidateIdTwo;
						maxScore = score;
					}
				}
			}
		}

		if (bestCandidateId == -1) {
			throw Exception(__FILE__, __LINE__, "There is no best candidate (available.size()==" + convertToString(static_cast<int> (available.size()))
			                + ", maxScore==" + convertToString(maxScore) + ")");
		}

		//Calcula las nuevas puntuaciones
		SnowFlake bestCandidate = available[bestCandidateId];
		SnowFlake bestCandidateTwo = available[bestCandidateIdTwo];
		currentSumIntra += bestCandidate.getSumIntraCompat() + bestCandidateTwo.getSumIntraCompat();
		Double currentSumInter = currentSumOneMinusInter, currentSumInterTwo = currentSumOneMinusInter;

		for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
			currentSumInter += 1.0 - problem_->maxPairwiseCompatibility((*it).ids(), bestCandidate.ids());
			currentSumInterTwo += 1.0 - problem_->maxPairwiseCompatibility((*it).ids(), bestCandidateTwo.ids());
		}

		Double sumInterCandidates = 1.0 - this->problem_->maxPairwiseCompatibility(bestCandidate.ids(), bestCandidateTwo.ids());
		currentSumOneMinusInter = currentSumInter + currentSumInterTwo + sumInterCandidates;
		//Marco como usado los candidatos usados
		canUseSnowFlake[bestCandidateId] = false;
		canUseSnowFlake[bestCandidateIdTwo] = false;
		//Agrego el elemento a la solucion
		selected->push_back(bestCandidate);
		selected->push_back(bestCandidateTwo);
	}

	return selected;
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByIntraInterProportional(SnowFlakeVector *produced, int numRequested)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	SnowFlake::sortByDecresingSumCompat(*produced);
	SnowFlakeVector available(*produced);
	SnowFlakeVector *selected = new SnowFlakeVector();
	Double currentSumIntra = 0.0;
	Double currentSumOneMinusInter = 0.0;

	while (selected->size() < numRequested && selected->size() < produced->size()) {
		Double maxScore = -1.0;
		int bestCandidateId = -1;

		if (available.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no available condidates");
		}

		int theSize = selected->size() + 1;

		for (Uint candidateId = 0; candidateId < available.size(); ++candidateId) {
			Double alpha = (Double) numRequested / theSize;
			Double beta = 0.0;

			if (theSize == 1) {
				beta = 1.0;
			}

			else {
				beta = alpha * ((Double) (numRequested - 1) / (Double) (theSize - 1));
			}

			SnowFlake candidate = available[candidateId];
			Double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter, alpha, beta);

			if (score > maxScore) {
				bestCandidateId = candidateId;
				maxScore = score;
			}
		}

		if (bestCandidateId == -1) {
			throw Exception(__FILE__, __LINE__, "There is no best candidate (available.size()==" + convertToString(static_cast<int> (available.size()))
			                + ", maxScore==" + convertToString(maxScore) + ")");
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

	//return selected;
	LocalSearchBundles localSearchBundles;
	SnowFlakeVector theFlakes = localSearchBundles.execute(1000,*selected, available, *this->problem_, this->interSimilarityWeight_);
	selected->clear();
	*selected = theFlakes;
	return selected;
}

Double ProduceAndChooseSolver::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter)
{
	Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
	Double sumOneMinusInter = selectedSumOneMinusInter;

	for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
		sumOneMinusInter += 1.0 - this->problem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
	}

	Double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double ProduceAndChooseSolver::scoreSetIntraInterWithSpecificProfile(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter)
{
	Double sumIntra = selectedSumIntra + candidate.getSumIntraCompatWithSpecificProfile();
	Double sumOneMinusInter = selectedSumOneMinusInter;

	for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
		sumOneMinusInter += 1.0 - this->problem_->maxPairwiseCompatibilityWithSpecificProfile(it->ids(), candidate.ids());
	}

	Double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double ProduceAndChooseSolver::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, SnowFlake& candidateTwo, Double selectedSumIntra, Double selectedSumOneMinusInter)
{
	Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat() + candidateTwo.getSumIntraCompat();
	Double sumInter = selectedSumOneMinusInter;
	Double sumInterTwo = selectedSumOneMinusInter;

	for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
		sumInter += 1.0 - this->problem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
		sumInterTwo += 1.0 - this->problem_->maxPairwiseCompatibility(it->ids(), candidateTwo.ids());
	}

	Double sumInterCandidates = 1.0 - this->problem_->maxPairwiseCompatibility(candidate.ids(), candidateTwo.ids());
	Double sumOneMinusInter = sumInter + sumInterTwo + sumInterCandidates;
	Double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

Double ProduceAndChooseSolver::scoreSetIntraInter(SnowFlakeVector* selected, SnowFlake& candidate, Double selectedSumIntra, Double selectedSumOneMinusInter, Double alpha, Double beta)
{
	Double sumIntra = selectedSumIntra + candidate.getSumIntraCompat();
	Double sumOneMinusInter = selectedSumOneMinusInter;

	for (SnowFlakeVector::iterator it = selected->begin(); it != selected->end(); ++it) {
		sumOneMinusInter += 1.0 - this->problem_->maxPairwiseCompatibility(it->ids(), candidate.ids());
	}

	Double gamma = 1.0 - this->interSimilarityWeight_;
	return (alpha * (gamma * sumIntra)) + (beta * ((1.0 - gamma) * sumOneMinusInter));
}

SnowFlakeVector* ProduceAndChooseSolver::getTopSolutionsByDensestSubgraph(SnowFlakeVector* produced, int numRequested)
{
	auto numProduced = produced->size();
	Double gamma = 1.0 - this->interSimilarityWeight_;
	MatrixWrapper* w;
	w = new MatrixConcrete(numProduced, numProduced);

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
	MapIntDouble weights = MapIntDouble();

	for (int ui = 0; ui < numProduced; ui++) {
		double weight = 0.0;

		for (int vi = 0; vi < numProduced; ++vi) {
			weight += w->get(ui,vi);
		}

		weights[ui] = weight;
		selected.insert(ui);
	}

	while(selected.size() > numRequested) {
		Double minWeightedDegree = std::numeric_limits<double>::max();
		int minElement = -1;

		for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
			Double weightedDegree = weights[*ui];

			if (weightedDegree < minWeightedDegree) {
				minWeightedDegree = weightedDegree;
				minElement = *ui;
			}
		}

		if (selected.count(minElement) == 0) {
			throw Exception(__FILE__, __LINE__, "Tried to remove element " + convertToString(minElement) + " that does not belong to " + "selected");
		}

		selected.erase(minElement);

		for (int ui = 0; ui < numProduced; ui++) {
			weights[ui] -= w->get(ui,minElement);
		}

	}

	SnowFlakeVector* solution = new SnowFlakeVector();

	for (IntSet::iterator ui = selected.begin(); ui != selected.end(); ++ui) {
		solution->push_back(produced->at(*ui));
	}

	return solution;
}
