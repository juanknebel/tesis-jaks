#include "greedySolver.h"
#include "../../../problem/factoryFlake.h"

// ESTA ES LA IMPLEMENTACION ORIGINAL
std::vector<SnowFlake> GreedySolver::produceManySnowflakes(int numSnowFlakes, ProblemInstance &theProblem)
{
	SnowFlake emptySnowFlake = SnowFlake();
	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (int i = 0; i < numSnowFlakes; ++i) {
		solution.push_back(emptySnowFlake);
	}

	std::set<Flake> theIds = FactoryFlake::createAllFlakes(theProblem);

	int idBestBundle = -1;
	Flake theBestId = Flake();
	double bestFnObjective = -1.0;

	int idBestWorstBundle = -1;
	Flake theBestWorstId = Flake();
	double bestWorstFnObjetive = -1.0;


	bool hasBetterFlake = false;
	bool hasBetterWorstFlake = false;
	bool isNotComplete = true;
	int kk = 0;

	while(isNotComplete) {
		double objective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);
		bestFnObjective = objective;
		bestWorstFnObjetive = -1.0;

		for(auto aFlake : theIds) {
			for (int i = 0; i < numSnowFlakes; ++i) {
				SnowFlake theSnowAtiPosition = solution[i];

				if (this->checkBudgetAndCoverageConstraint(theSnowAtiPosition.ids(), aFlake, theProblem)) {
					std::set<Flake> tempIds(theSnowAtiPosition.ids());
					tempIds.insert(aFlake);
					SnowFlake theSnow(tempIds);
					solution[i] = theSnow;
					double newFnObjective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);

					if (newFnObjective >= bestFnObjective) {
						bestFnObjective = newFnObjective;
						idBestBundle = i;
						hasBetterFlake = true;
						theBestId = aFlake;
					}

					else {
						if (newFnObjective >= bestWorstFnObjetive) {
							bestWorstFnObjetive = newFnObjective;
							idBestWorstBundle = i;
							hasBetterWorstFlake = true;
							theBestWorstId = aFlake;
						}
					}

					solution[i] = theSnowAtiPosition;
				}
			}
		}

		if (hasBetterFlake) {
			std::set<Flake> theNewIdsForBundle(solution[idBestBundle].ids());
			theNewIdsForBundle.insert(theBestId);
			SnowFlake theNewBestSnowFlake(theNewIdsForBundle);
			solution[idBestBundle] = theNewBestSnowFlake;
			theIds.erase(theBestId);
		}

		else {
			if (hasBetterWorstFlake) {
				std::set<Flake> theNewIdsForBundle(solution[idBestWorstBundle].ids());
				theNewIdsForBundle.insert(theBestWorstId);
				SnowFlake theNewBestWorstSnowFlake(theNewIdsForBundle);
				solution[idBestWorstBundle] = theNewBestWorstSnowFlake;
				theIds.erase(theBestWorstId);
			}
		}

		isNotComplete = hasBetterFlake || hasBetterWorstFlake;
		hasBetterFlake = false;
		hasBetterWorstFlake = false;
	}

	return solution;
}

// ESTA ES LA VERSION QUE SOLO MAXIMIZA LA FUNCION OBJECTIVO
std::vector<SnowFlake> GreedySolver::produceManySnowflakes1(int numSnowFlakes, ProblemInstance &theProblem)
{
	SnowFlake emptySnowFlake = SnowFlake();
	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (int i = 0; i < numSnowFlakes; ++i) {
		solution.push_back(emptySnowFlake);
	}

	std::set<Flake> theIds = FactoryFlake::createAllFlakes(theProblem);
	int idBestBundle = -1;
	Flake theBestId = Flake();
	double bestFnObjective = -1.0;
	bool hasBetterFlake = false;
	bool isNotComplete = true;

	while(isNotComplete) {
		double objective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);
		bestFnObjective = objective;

		for(auto aFlake : theIds) {
			for (int i = 0; i < numSnowFlakes; ++i) {
				SnowFlake theSnowAtiPosition = solution[i];
				if (this->checkBudgetAndCoverageConstraint(theSnowAtiPosition.ids(), aFlake, theProblem)) {
					std::set<Flake> tempIds(theSnowAtiPosition.ids());
					tempIds.insert(aFlake);
					SnowFlake theSnow(tempIds);
					solution[i] = theSnow;
					double newFnObjective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);

					if (newFnObjective >= bestFnObjective) {
						bestFnObjective = newFnObjective;
						idBestBundle = i;
						hasBetterFlake = true;
						theBestId = aFlake;
					}
				}

				solution[i] = theSnowAtiPosition;
			}
		}

		if (hasBetterFlake == true) {
			std::set<Flake> theNewIdsForBundle(solution[idBestBundle].ids());
			theNewIdsForBundle.insert(theBestId);
			SnowFlake theNewBestSnowFlake(theNewIdsForBundle);
			solution[idBestBundle] = theNewBestSnowFlake;
			theIds.erase(theBestId);
		}

		isNotComplete = hasBetterFlake;
		hasBetterFlake = false;
	}

	return solution;
}

// ESTA ES LA VERSION QUE ADMITE REPETIDOS
std::vector<SnowFlake> GreedySolver::produceManySnowflakes2(int numSnowFlakes, ProblemInstance &theProblem)
{
	SnowFlake emptySnowFlake = SnowFlake();
	std::vector<SnowFlake> solution = std::vector<SnowFlake>();
	std::vector<int> hashValueBundles;

	for (int i = 0; i < numSnowFlakes; ++i) {
		solution.push_back(emptySnowFlake);
		hashValueBundles.push_back(0);
	}

	std::set<Flake> theIds = FactoryFlake::createAllFlakes(theProblem);
	int idBestBundle = -1;
	Flake theBestId = Flake();
	double bestFnObjective = -1.0;
	bool hasBetterFlake = false;
	bool isNotComplete = true;

	while(isNotComplete) {
		double objective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);
		bestFnObjective = objective;

		for(auto aFlake : theIds) {
			for (int i = 0; i < numSnowFlakes; ++i) {
				SnowFlake theSnowAtiPosition = solution[i];
				int newHashValue = hashValueBundles[i] + aFlake.getId() + 1;
				bool existSameBundle = false;

				for (int j = 0; j < numSnowFlakes; ++j) {
					existSameBundle = existSameBundle || (newHashValue == hashValueBundles[j]);
				}

				if (theSnowAtiPosition.ids().count(aFlake) == 0 && !existSameBundle) {
					if (this->checkBudgetAndCoverageConstraint(theSnowAtiPosition.ids(), aFlake, theProblem)) {
						std::set<Flake> tempIds(theSnowAtiPosition.ids());
						tempIds.insert(aFlake);
						SnowFlake theSnow(tempIds);
						solution[i] = theSnow;
						double newFnObjective = SnowFlake::objetiveFunction(solution, this->interSimilarityWeight_, theProblem);

						if (newFnObjective >= bestFnObjective) {
							bestFnObjective = newFnObjective;
							idBestBundle = i;
							hasBetterFlake = true;
							theBestId = aFlake;
						}
					}

					solution[i] = theSnowAtiPosition;
				}
			}
		}

		if (hasBetterFlake) {
			std::set<Flake> theNewIdsForBundle(solution[idBestBundle].ids());
			theNewIdsForBundle.insert(theBestId);
			SnowFlake theNewBestSnowFlake(theNewIdsForBundle);
			solution[idBestBundle] = theNewBestSnowFlake;
			hashValueBundles[idBestBundle] = hashValueBundles[idBestBundle] + theBestId.getId() + 1;
		}

		isNotComplete = hasBetterFlake;
		hasBetterFlake = false;
	}

	return solution;
}
