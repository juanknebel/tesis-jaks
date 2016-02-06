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
        SnowFlakeVector iterationSolution(temporarySolution.begin(), temporarySolution.end());
        ++iteration;
        this->updateTabuElements(setOfTabuBundles);
        SnowFlake worstSnowFlake = this->getWorstBundle(iterationSolution, setOfTabuBundles, theProblem, interSimilarityWeight);
        SnowFlake centroidSnowFlake = this->getCentroidBundle(worstSnowFlake, iterationSolution, theProblem,
                                                              interSimilarityWeight);
        SnowFlakeVector betterFlakes = this->getBetterFlakes(centroidSnowFlake, setOfTabuBundles, remainingFlakes,
                                                             theProblem);

        double betterInterFunction = SnowFlake::objetiveFunction(iterationSolution, 1);
        SnowFlake bestBundle;
        bool betterSolution = false;

        SnowFlake worstBundle;
        bool betterWorstSolution = false;
        double bestWorstObjectiveFunction = std::numeric_limits<double>::min();

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
            if (newInterFunction > betterInterFunction) {
                betterSolution = true;
                bestBundle = aFlake;
                betterInterFunction = newInterFunction;
            }
            else {
                //Si no mejora la solucion
                if (!betterSolution && newInterFunction > bestWorstObjectiveFunction
                    && countTabuBundles[aFlake.getIdentificator()] > 2) {
                    betterWorstSolution = true;
                    bestWorstObjectiveFunction = newInterFunction;
                    worstBundle = aFlake;
                }
            }
        }
        if (betterSolution) {
            temporarySolution.clear();
            temporarySolution.push_back(bestBundle);
            for (auto bundle : iterationSolution) {
                if (bundle.getIdentificator() != worstSnowFlake.getIdentificator()) {
                    temporarySolution.push_back(bundle);
                }
            }
            double tempObjectiveFunction = SnowFlake::objetiveFunction(temporarySolution, interSimilarityWeight);
            if (tempObjectiveFunction > currentObjectiveFunction) {
                bestSolution.clear();
                bestSolution = temporarySolution;
                currentObjectiveFunction = tempObjectiveFunction;
            }
            remainingFlakes.erase(std::remove_if(remainingFlakes.begin(),
                                                 remainingFlakes.end(),
                                                 [bestBundle](SnowFlake aFlake){
                                                     return aFlake.getIdentificator() == bestBundle.getIdentificator();
                                                 }),
                                  remainingFlakes.end());
            remainingFlakes.push_back(worstSnowFlake);
        }
        else {
            if (betterWorstSolution) {
                temporarySolution.clear();
                temporarySolution.push_back(worstBundle);
                for (auto bundle : iterationSolution) {
                    if (bundle.getIdentificator() != worstSnowFlake.getIdentificator()) {
                        temporarySolution.push_back(bundle);
                    }
                }
                remainingFlakes.erase(std::remove_if(remainingFlakes.begin(),
                                                     remainingFlakes.end(),
                                                     [worstBundle](SnowFlake aFlake){
                                                         return aFlake.getIdentificator() == worstBundle.getIdentificator();
                                                     }),
                                      remainingFlakes.end());
                remainingFlakes.push_back(worstSnowFlake);
            }
            else {
                for (SnowFlake betterFlake : betterFlakes) {
                    countTabuBundles[betterFlake.getIdentificator()] = countTabuBundles[betterFlake.getIdentificator()] + 1;
                }
            }
        }
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
    double minPairwise = std::numeric_limits<double>::min();
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
                                                    SnowFlakeVector &remainingFlakes, ProblemInstance &theProblem) {
    SnowFlakeVector bestBundles;
    SnowFlakeVector temporaryFlakes;
    temporaryFlakes.push_back(centroid);
    double objectiveFunction = std::numeric_limits<double>::min();
    double objectiveFunctionTwo = std::numeric_limits<double>::min();
    for (auto bundle : remainingFlakes) {
        if (setOfTabuBundles[bundle.getIdentificator()] == 0) {
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
    }
    return bestBundles;
}
