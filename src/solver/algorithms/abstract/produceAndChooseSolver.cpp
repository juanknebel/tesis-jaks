/*
 * produceAndChooseSolver.cpp
 *
 *  Created on: 06/08/2013
 *      Author: jknebel
 */

#include "produceAndChooseSolver.h"
#include "../../../util/algorithm/localSearchBundles.h"

void ProduceAndChooseSolver::setRankingStrategy(ProduceAndChooseSolver::RankingStrategy strategy)
{
	this->rankingStrategy_ = strategy;
}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getRankingStrategy()
{
	return this->rankingStrategy_;
}

std::vector<SnowFlake> ProduceAndChooseSolver::solve(ProblemInstance& theProblem, int numSnowFlakes)
{
	std::vector<SnowFlake> produced = this->produceManySnowflakes(numSnowFlakes, theProblem);
	SnowFlake::sortByDecresingSumCompat(produced, theProblem);
	produced = this->getTopSolutionByRankingStrategy(produced, numSnowFlakes, theProblem);
	return produced;
}

std::vector<SnowFlake> ProduceAndChooseSolver::getTopSolutionByRankingStrategy(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem)
{
	std::vector<SnowFlake> ret;

	switch (this->rankingStrategy_) {
	case ProduceAndChooseSolver::RANK_BY_INTRA:
		ret = this->getTopSolutionsByIntra(produced, numRequested, theProblem);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByInterIntra(produced, numRequested, theProblem);
		break;

	case ProduceAndChooseSolver::RANK_BY_DENSEST_SUBGRAPH:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByDensestSubgraph(produced, numRequested, theProblem);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER_TUPLE:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByInterIntraByTuples(produced, numRequested, theProblem);
		break;

	case ProduceAndChooseSolver::RANK_BY_INTRA_INTER_PROPORTIONAL:
		if (this->interSimilarityWeight_ < 0.0) {
			throw Exception(__FILE__, __LINE__, "This ranking strategy requires an inter similarity weight");
		}

		ret = this->getTopSolutionsByIntraInterProportional(produced, numRequested, theProblem);
		break;

	default:
		break;
	}
	return ret;
}

ProduceAndChooseSolver::RankingStrategy ProduceAndChooseSolver::getDefault()
{
	return RANK_BY_INTRA;
}

std::vector<SnowFlake>
ProduceAndChooseSolver::getTopSolutionsByIntra(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem)
{
	SnowFlake::sortByDecresingSumCompat(produced, theProblem);
	auto minValue = ((numRequested < produced.size()) ? numRequested : produced.size());
	std::vector<SnowFlake> selected = std::vector<SnowFlake>();

	for (int i = 0; i < minValue; ++i) {
		SnowFlake selectedSnowFlake(produced.at(i));
		selected.push_back(selectedSnowFlake);
	}

	return selected;
}

std::vector<SnowFlake>
ProduceAndChooseSolver::getTopSolutionsByInterIntra(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	//SnowFlake::sortByDecresingSumCompat(*produced);
	std::vector<SnowFlake> remainingFlakes(produced);
	std::vector<SnowFlake> selected = std::vector<SnowFlake>();
	double currentSumIntra = 0.0;
	double currentSumOneMinusInter = 0.0;

	while (selected.size() < numRequested && selected.size() < produced.size()) {
		double maxScore = -1.0;
		int bestCandidateId = -1;

		if (remainingFlakes.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no remainingFlakes condidates");
		}

		for (int candidateId = 0; candidateId < remainingFlakes.size(); ++candidateId) {
			SnowFlake candidate = remainingFlakes[candidateId];
			double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter,
                                              theProblem);

			//double score = scoreSetIntraInterWithSpecificProfile(selected, candidate, currentSumIntra, currentSumOneMinusInter);
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
		currentSumIntra += SnowFlake::getSumIntraCompat(bestCandidate, theProblem);

		for (auto aFlake : selected) {
			currentSumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, bestCandidate, theProblem);
		}

		//Borro el candidato que ya use
		remainingFlakes.erase(remainingFlakes.begin() + bestCandidateId);
		//Agrego el elemento a la solucion
		selected.push_back(bestCandidate);
	}

	LocalSearchBundles localSearchBundles;
	std::vector<SnowFlake> theFlakes = localSearchBundles.execute(1000,selected, remainingFlakes, theProblem, this->interSimilarityWeight_);
	return theFlakes;
}

std::vector<SnowFlake> ProduceAndChooseSolver::getTopSolutionsByInterIntraByTuples(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	SnowFlake::sortByDecresingSumCompat(produced, theProblem);
	std::vector<SnowFlake> available(produced);
	int sizeOfBundles = produced.size();
    std::vector<bool> canUseSnowFlake;

	for (int i = 0; i < sizeOfBundles; ++i) {
		canUseSnowFlake.push_back(true);
	}

	std::vector<SnowFlake> selected = std::vector<SnowFlake>();
	double currentSumIntra = 0.0;
	double currentSumOneMinusInter = 0.0;

	while (selected.size() < numRequested && selected.size() < produced.size()) {
		double maxScore = -1.0;
		int bestCandidateId = -1;
		int bestCandidateIdTwo = -1;

		if (available.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no available condidates");
		}

		for (int candidateId = 0; candidateId < sizeOfBundles; ++candidateId) {
			for (int candidateIdTwo = candidateId + 1; candidateIdTwo < sizeOfBundles; ++candidateIdTwo) {
				if (canUseSnowFlake[candidateId] && canUseSnowFlake[candidateIdTwo]) {
					SnowFlake candidate = available[candidateId];
					SnowFlake candidateTwo = available[candidateIdTwo];
					double score = scoreSetIntraInter(selected, candidate, candidateTwo, currentSumIntra,
                                                      currentSumOneMinusInter, theProblem);

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
		currentSumIntra += SnowFlake::getSumIntraCompat(bestCandidate, theProblem) + SnowFlake::getSumIntraCompat(bestCandidateTwo, theProblem);
		double currentSumInter = currentSumOneMinusInter, currentSumInterTwo = currentSumOneMinusInter;

		for (auto aFlake : selected) {
			currentSumInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, bestCandidate, theProblem);
			currentSumInterTwo += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, bestCandidateTwo, theProblem);
		}

		double sumInterCandidates = 1.0 - SnowFlake::maxPairwiseCompatibility(bestCandidate, bestCandidateTwo, theProblem);
		currentSumOneMinusInter = currentSumInter + currentSumInterTwo + sumInterCandidates;
		//Marco como usado los candidatos usados
		canUseSnowFlake[bestCandidateId] = false;
		canUseSnowFlake[bestCandidateIdTwo] = false;
		//Agrego el elemento a la solucion
		selected.push_back(bestCandidate);
		selected.push_back(bestCandidateTwo);
	}

	return selected;
}

std::vector<SnowFlake>
ProduceAndChooseSolver::getTopSolutionsByIntraInterProportional(std::vector<SnowFlake> &produced, int numRequested,
                                                                ProblemInstance &theProblem)
{
	if(this->interSimilarityWeight_ < 0.00) {
		throw Exception(__FILE__, __LINE__, "You need to set the value of inter similarity weight");
	}

	SnowFlake::sortByDecresingSumCompat(produced, theProblem);
	std::vector<SnowFlake> available(produced);
	std::vector<SnowFlake> selected = std::vector<SnowFlake>();
	double currentSumIntra = 0.0;
	double currentSumOneMinusInter = 0.0;

	while (selected.size() < numRequested && selected.size() < produced.size()) {
		double maxScore = -1.0;
		int bestCandidateId = -1;

		if (available.size() == 0) {
			throw Exception(__FILE__, __LINE__, "There are no available condidates");
		}

		int theSize = selected.size() + 1;

		for (int candidateId = 0; candidateId < available.size(); ++candidateId) {
			double alpha = (double) numRequested / theSize;
			double beta = 0.0;

			if (theSize == 1) {
				beta = 1.0;
			}

			else {
				beta = alpha * ((double) (numRequested - 1) / (double) (theSize - 1));
			}

			SnowFlake candidate = available[candidateId];
			double score = scoreSetIntraInter(selected, candidate, currentSumIntra, currentSumOneMinusInter, alpha,
                                              beta, theProblem);

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
		currentSumIntra += SnowFlake::getSumIntraCompat(bestCandidate, theProblem);

		for (auto aFlake : selected) {
			currentSumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, bestCandidate, theProblem);
		}

		//Borro el candidato que ya use
		available.erase(available.begin() + bestCandidateId);
		//Agrego el elemento a la solucion
		selected.push_back(bestCandidate);
	}

	//return selected;
	LocalSearchBundles localSearchBundles;
	std::vector<SnowFlake> theFlakes = localSearchBundles.execute(1000,selected, available, theProblem, this->interSimilarityWeight_);
	return theFlakes;
}

double ProduceAndChooseSolver::scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                                  double selectedSumOneMinusInter, ProblemInstance &theProblem)
{
	double sumIntra = selectedSumIntra + SnowFlake::getSumIntraCompat(candidate, theProblem);
	double sumOneMinusInter = selectedSumOneMinusInter;

	for (auto aFlake : selected) {
		sumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, candidate, theProblem);
	}

	double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double ProduceAndChooseSolver::scoreSetIntraInterWithSpecificProfile(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                                                     double selectedSumOneMinusInter, ProblemInstance &theProblem)
{
	double sumIntra = selectedSumIntra + SnowFlake::getSumIntraCompatWithSpecificProfile(candidate, theProblem);
	double sumOneMinusInter = selectedSumOneMinusInter;

	for (auto aFlake : selected) {
		sumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, candidate, theProblem);
	}

	double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double ProduceAndChooseSolver::scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, SnowFlake &candidateTwo,
                                                  double selectedSumIntra, double selectedSumOneMinusInter, ProblemInstance &theProblem)
{
	double sumIntra = selectedSumIntra + SnowFlake::getSumIntraCompat(candidate, theProblem) + SnowFlake::getSumIntraCompat(candidateTwo, theProblem);
	double sumInter = selectedSumOneMinusInter;
	double sumInterTwo = selectedSumOneMinusInter;

	for (auto aFlake : selected) {
		sumInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, candidate, theProblem);
		sumInterTwo += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, candidateTwo, theProblem);
	}

	double sumInterCandidates = 1.0 - SnowFlake::maxPairwiseCompatibility(candidate, candidateTwo, theProblem);
	double sumOneMinusInter = sumInter + sumInterTwo + sumInterCandidates;
	double gamma = 1.0 - this->interSimilarityWeight_;
	return (gamma * sumIntra) + ((1.0 - gamma) * sumOneMinusInter);
}

double ProduceAndChooseSolver::scoreSetIntraInter(std::vector<SnowFlake> &selected, SnowFlake &candidate, double selectedSumIntra,
                                                  double selectedSumOneMinusInter, double alpha, double beta, ProblemInstance &theProblem)
{
	double sumIntra = selectedSumIntra + SnowFlake::getSumIntraCompat(candidate, theProblem);
	double sumOneMinusInter = selectedSumOneMinusInter;

	for (auto aFlake : selected) {
		sumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(aFlake, candidate, theProblem);
	}

	double gamma = 1.0 - this->interSimilarityWeight_;
	return (alpha * (gamma * sumIntra)) + (beta * ((1.0 - gamma) * sumOneMinusInter));
}

std::vector<SnowFlake> ProduceAndChooseSolver::getTopSolutionsByDensestSubgraph(std::vector<SnowFlake> &produced, int numRequested, ProblemInstance &theProblem)
{
	int numProduced = produced.size();
	double gamma = 1.0 - this->interSimilarityWeight_;

    unique_ptr<MatrixWrapper> myPtr(new MatrixConcrete(numProduced, numProduced));
    MatrixWrapper* w = myPtr.get();

	for (int ui = 0; ui < numProduced; ++ui) {
		SnowFlake& u = produced[ui];

		for (int vi = 0; vi < numProduced; ++vi) {
			SnowFlake& v = produced[vi];
			double val = ((gamma / (2.0 * ((double) numRequested - 1.0))) * (SnowFlake::getSumIntraCompat(u, theProblem) + SnowFlake::getSumIntraCompat(v, theProblem))
			             + (1.0 - gamma) * (1.0 - SnowFlake::maxPairwiseCompatibility(u, v, theProblem)));
			w->set(ui,vi,val);
		}
	}

	std::set<int> selected = std::set<int>();
    std::map<int, double> weights = std::map<int, double>();

	for (int ui = 0; ui < numProduced; ui++) {
		double weight = 0.0;

		for (int vi = 0; vi < numProduced; ++vi) {
			weight += w->get(ui,vi);
		}

		weights[ui] = weight;
		selected.insert(ui);
	}

	while(selected.size() > numRequested) {
		double minWeightedDegree = std::numeric_limits<double>::max();
		int minElement = -1;

		for (auto ui : selected) {
			double weightedDegree = weights[ui];

			if (weightedDegree < minWeightedDegree) {
				minWeightedDegree = weightedDegree;
				minElement = ui;
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

	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (auto ui : selected) {
		solution.push_back(produced.at(ui));
	}

	return solution;
}
