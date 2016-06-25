//
// Created by zero on 18/08/15.
//

#include "localSearchBundles.h"
#include "../system/exception.h"
#include "../logger/logger.h"

SnowFlakeVector LocalSearchBundles::execute(int maxIteration, SnowFlakeVector &solution,
                                                   SnowFlakeVector &remainingFlakes, ProblemInstance &theProblem,
                                                   Double interSimilarityWeight) {
    TabuBundles setOfTabuBundles;
    int tabuBundleCount = 10;
    SnowFlakeVector visitSolution(solution.begin(), solution.end());

    int id = 0;
    for (auto& snowFlake : visitSolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
    }

    for (auto& remainingFlake : remainingFlakes) {
        remainingFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
    }

    SnowFlakeVector bestSolution(visitSolution.begin(), visitSolution.end());
    double theBestObjectiveSolution = SnowFlake::objetiveFunction(bestSolution, interSimilarityWeight);

    int iteration = 1;
    while (iteration < maxIteration) {
        SnowFlakeVector iterationSolution(visitSolution.begin(), visitSolution.end());
        ++iteration;
        this->updateTabuElements(setOfTabuBundles);
        SnowFlake worstSnowFlake = this->getWorstBundle(iterationSolution, setOfTabuBundles, theProblem, interSimilarityWeight);
        SnowFlake centroidSnowFlake = this->getCentroidBundle(worstSnowFlake, iterationSolution, theProblem,
                                                              interSimilarityWeight);
        SnowFlakeVector betterFlakes = this->getBetterFlakes(centroidSnowFlake, setOfTabuBundles, remainingFlakes,
                                                             theProblem,false);

        double itBetterInterFunction = -1.0;
        SnowFlake bestBundle;
        for (auto aFlake : betterFlakes) {
            SnowFlakeVector aNewSolution;
            aNewSolution.push_back(aFlake);
            for (auto aFlakeInSolution : iterationSolution) {
                if (aFlakeInSolution.getIdentificator() != worstSnowFlake.getIdentificator()) {
                    aNewSolution.push_back(aFlakeInSolution);
                }
            }
            double newInterFunction = SnowFlake::objetiveFunction(aNewSolution, 1);

            //Si mejora la solucion
            if (newInterFunction > itBetterInterFunction) {
                bestBundle = aFlake;
                itBetterInterFunction = newInterFunction;
            }
        }
        
        if (true) {
	    SnowFlakeVector betterFlakes = this->getBetterFlakes(centroidSnowFlake, setOfTabuBundles, remainingFlakes,
                                                             theProblem,true);
	    SnowFlake tabuBetterBundle;
	    tabuBetterBundle.setIdentificator(-1);
	    double tabuItBestObjectiveFunction = itBetterInterFunction * 1.2;
	    double valueToTakeOffTabuList = itBetterInterFunction * 0.9;
	    TabuBundles elementsToTakeOffTabeList;
	    for (auto aFlake : betterFlakes) {
		SnowFlakeVector aNewSolution;
		aNewSolution.push_back(aFlake);
		for (auto aFlakeInSolution : iterationSolution) {
		    if (aFlakeInSolution.getIdentificator() != worstSnowFlake.getIdentificator()) {
			aNewSolution.push_back(aFlakeInSolution);
		    }
		}
		double newInterFunction = SnowFlake::objetiveFunction(aNewSolution, 1);

		//Si mejora la solucion
		if (newInterFunction > tabuItBestObjectiveFunction) {
		    tabuBetterBundle = aFlake;
		    tabuItBestObjectiveFunction = newInterFunction;
		}
		else {
		    if (newInterFunction > valueToTakeOffTabuList) {
			elementsToTakeOffTabeList.push_back(aFlake.getIdentificator());
		    }
		}
	    }
	    
	    if (tabuBetterBundle.getIdentificator() == -1) {
		bestBundle = tabuBetterBundle;
	    }
	    
	    for (auto aFlake : elementsToTakeOffTabeList) {
		setOfTabuBundles[aFlake] = 0;
	    }
	}
	
	visitSolution.clear();
	visitSolution.push_back(bestBundle);
	for (auto bundle : iterationSolution) {
	    if (bundle.getIdentificator() != worstSnowFlake.getIdentificator()) {
		visitSolution.push_back(bundle);
	    }
	}
	
	double tempObjectiveFunction = SnowFlake::objetiveFunction(visitSolution, interSimilarityWeight);
	if (tempObjectiveFunction > theBestObjectiveSolution) {
	    bestSolution.clear();
	    bestSolution = visitSolution;
	    theBestObjectiveSolution = tempObjectiveFunction;
	}
	remainingFlakes.erase(std::remove_if(remainingFlakes.begin(),
					      remainingFlakes.end(),
					      [bestBundle](SnowFlake aFlake){
						  return aFlake.getIdentificator() == bestBundle.getIdentificator();
					      }),
			      remainingFlakes.end());
	remainingFlakes.push_back(worstSnowFlake);
        setOfTabuBundles[worstSnowFlake.getIdentificator()] = tabuBundleCount;
    }
    return bestSolution;
}

void LocalSearchBundles::updateTabuElements(std::vector<int> &tabuSet) {
    for (auto& tabuElement : tabuSet) {
        if (tabuElement > 0) {
            tabuElement--;
        }
    }
}

SnowFlake LocalSearchBundles::getWorstBundle(SnowFlakeVector &solution, TabuBundles setOfTabuBundles,
                                             ProblemInstance &theProblem, Double intersimilarityWeight) {
    double worstValue = std::numeric_limits<double>::max();
    SnowFlake worstSnowFlake;
    for (auto bundle : solution) {
        if (setOfTabuBundles[bundle.getIdentificator()] == 0) {
            double value = 0.0;//(1 - intersimilarityWeight) * bundle.getSumIntraCompat();
            for (auto otherBundle : solution) {
                if (bundle.getIdentificator() != otherBundle.getIdentificator()) {
                    value += (1 - theProblem.maxPairwiseCompatibility(bundle.ids(), otherBundle.ids()));
                }
            }
            if (value < worstValue) {
                worstValue = value;
                worstSnowFlake = bundle;
            }
        }
    }
    return worstSnowFlake;
}

SnowFlake LocalSearchBundles::getCentroidBundle(SnowFlake worstBundle, SnowFlakeVector &solution,
                                                ProblemInstance &theProblem, Double interSimilarityWeight) {
    SnowFlake centroid;
    double minPairwise = -1.0;
    for (auto bundle : solution) {
        if (worstBundle.getIdentificator() != bundle.getIdentificator()) {
            double value = 0.0;
            for (auto otherBundle : solution) {
                if (bundle.getIdentificator() != otherBundle.getIdentificator()
                    && otherBundle.getIdentificator() != worstBundle.getIdentificator()) {
                    value += (1 - theProblem.maxPairwiseCompatibility(bundle.ids(), otherBundle.ids()));
                }
            }
            if (value > minPairwise) {
                minPairwise = value;
                centroid = bundle;
            }
        }
    }
    return centroid;
}

SnowFlakeVector LocalSearchBundles::getBetterFlakes(SnowFlake centroid, TabuBundles setOfTabuBundles,
                                                    SnowFlakeVector &remainingFlakes, ProblemInstance &theProblem, bool takeTabu) {
    SnowFlakeVector bestBundles;
    SnowFlakeVector temporaryFlakes;
    temporaryFlakes.push_back(centroid);
    double objectiveFunction = -1.0;
    double objectiveFunctionTwo = -1.0;
    for (auto bundle : remainingFlakes) {
        if ((takeTabu && setOfTabuBundles[bundle.getIdentificator()] > 0) ||
	   (!takeTabu && setOfTabuBundles[bundle.getIdentificator()] == 0)) {
            temporaryFlakes.push_back(bundle);
            double newFunction = SnowFlake::objetiveFunction(temporaryFlakes, 1);
            if (newFunction > objectiveFunction) {
                if (newFunction > objectiveFunctionTwo) {
                    objectiveFunctionTwo = newFunction;
                }
                else {
                    objectiveFunction = newFunction;
                }
                bestBundles.push_back(bundle);
            }
            temporaryFlakes.pop_back();
        }
        else {
	    
	}
    }
    return bestBundles;
}
