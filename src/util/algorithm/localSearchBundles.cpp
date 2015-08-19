//
// Created by zero on 18/08/15.
//

#include "localSearchBundles.h"
#include "../system/exception.h"
#include "../logger/logger.h"

SnowFlakeVector LocalSearchBundles::execute(int maxIteration, SnowFlakeVector &solution,
                                                   SnowFlakeVector &remainingFlakes, ProblemInstance &theProblem,
                                                   Double interSimilarityWeight) {
    DEBUG(DBG_DEBUG, "entro al tabu");
    TabuBundles setOfTabuBundles;
    TabuBundles countTabuBundles;
    int tabuBundleCount = 10;
    SnowFlakeVector temporarySolution(solution.begin(), solution.end());

    int id = 0;
    for (auto& snowFlake : temporarySolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        countTabuBundles.push_back(0);
    }

    for (auto& remainingFlake : remainingFlakes) {
        remainingFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        countTabuBundles.push_back(0);
    }

    SnowFlakeVector bestSolution(temporarySolution.begin(), temporarySolution.end());
    double currentObjectiveFunction = SnowFlake::objetiveFunction(bestSolution, interSimilarityWeight);

    int iteration = 1;
    while (iteration < maxIteration) {
        DEBUG(DBG_DEBUG, "iteracion: "<<iteration);
        SnowFlakeVector iterationSolution(temporarySolution.begin(), temporarySolution.end());
        ++iteration;
        this->updateTabuElements(setOfTabuBundles);
        SnowFlake worstSnowFlake = this->getWorstBundle(iterationSolution, setOfTabuBundles, theProblem, interSimilarityWeight);
        SnowFlake centroidSnowFlake = this->getCentroidBundle(iterationSolution, theProblem, interSimilarityWeight);
        SnowFlakeVector betterFlakes = this->getBetterFlakes(centroidSnowFlake, setOfTabuBundles, remainingFlakes,
                                                             theProblem, interSimilarityWeight);

        double betterObjectiveFunction = std::numeric_limits<double>::min();
        SnowFlake flakeToReplace;
        bool betterSolution = false;

        for (auto aFlake : betterFlakes) {
            SnowFlakeVector aNewSolution;
            aNewSolution.push_back(aFlake);
            for (auto aFlakeInSolution : iterationSolution) {
                if (aFlakeInSolution.getIdentificator() != worstSnowFlake.getIdentificator()) {
                    aNewSolution.push_back(aFlakeInSolution);
                }
            }
            double newObjectiveFunction = SnowFlake::objetiveFunction(aNewSolution, interSimilarityWeight);
            if (newObjectiveFunction > betterObjectiveFunction) {
                betterSolution = true;
                flakeToReplace = aFlake;
                betterObjectiveFunction = newObjectiveFunction;
            }
        }
        if (betterSolution) {
            temporarySolution.clear();
            temporarySolution.push_back(flakeToReplace);
            for (auto bundle : iterationSolution) {
                if (bundle.getIdentificator() != worstSnowFlake.getIdentificator()) {
                    temporarySolution.push_back(bundle);
                }
            }
            if (betterObjectiveFunction > currentObjectiveFunction) {
                bestSolution.clear();
                bestSolution = temporarySolution;
                currentObjectiveFunction = betterObjectiveFunction;
            }
            remainingFlakes.erase(std::remove_if(remainingFlakes.begin(),
                                                 remainingFlakes.end(),
                                                 [flakeToReplace](SnowFlake aFlake){
                                                     return aFlake.getIdentificator() == flakeToReplace.getIdentificator();
                                                 }),
                                  remainingFlakes.end());
            remainingFlakes.push_back(worstSnowFlake);
            setOfTabuBundles[worstSnowFlake.getIdentificator()] = tabuBundleCount;
        }

    }
    DEBUG(DBG_DEBUG, "sale del tabu");
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
        double value = (1 - intersimilarityWeight) * bundle.getSumIntraCompat();
        for (auto otherBundle : solution) {
            if (bundle.getIdentificator() != otherBundle.getIdentificator()) {
                value += theProblem.maxPairwiseCompatibility(bundle.ids(), otherBundle.ids());
            }
        }
        if (value < worstValue) {
            worstValue = value;
            worstSnowFlake = bundle;
        }
    }

    return worstSnowFlake;
}

SnowFlake LocalSearchBundles::getCentroidBundle(SnowFlakeVector &solution, ProblemInstance &theProblem,
                                                Double interSimilarityWeight) {
    SnowFlake centroid;
    double minPairwise = std::numeric_limits<double>::max();
    for (auto bundle : solution) {
        double value = 0.0;
        for (auto otherBundle : solution) {
            if (bundle.getIdentificator() != otherBundle.getIdentificator()) {
                value += theProblem.maxPairwiseCompatibility(bundle.ids(), otherBundle.ids());
            }
        }
        if (value < minPairwise) {
            minPairwise = value;
            centroid = bundle;
        }
    }
    return centroid;
}

SnowFlakeVector LocalSearchBundles::getBetterFlakes(SnowFlake centroid, TabuBundles setOfTabuBundles, SnowFlakeVector &remainingFlakes,
                                ProblemInstance &theProblem, double interSimilarityWeight) {
    SnowFlakeVector bestBundles;
    SnowFlakeVector temporaryFlakes;
    temporaryFlakes.push_back(centroid);
    double objectiveFunction = std::numeric_limits<double>::min();
    double objectiveFunctionTwo = std::numeric_limits<double>::min();
    for (auto bundle : remainingFlakes) {
        if (setOfTabuBundles[bundle.getIdentificator()] == 0) {
            temporaryFlakes.push_back(bundle);
            double newFunction = SnowFlake::objetiveFunction(temporaryFlakes, interSimilarityWeight);
            if (newFunction > objectiveFunction) {
                if (newFunction > objectiveFunctionTwo) {
                    objectiveFunctionTwo = newFunction;
                }
                else {
                    objectiveFunction = newFunction;
                }
                bestBundles.push_back(bundle);
            }
        }
        temporaryFlakes.pop_back();
    }
    return std::vector<SnowFlake>();
}
