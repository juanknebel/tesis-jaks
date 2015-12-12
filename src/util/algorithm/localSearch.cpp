#include "localSearch.h"
#include "../system/exception.h"
#include "../logger/logger.h"

SnowFlakeVector LocalSearch::execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight) {
    /*
     * Tomo un bundle:
     * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
     * si mejora hago efectivo el cambio y paso al siguiente elemento
     * si no mejora intento con otro elemento
     * esto lo repito tantas veces como el parametro de maximas iteraciones
    */
    SnowFlakeVector temporarySolution(solution.begin(), solution.end());
    int id = 0;
    int tabuBundleCount = 10;
    int tabuElementCount = 5;

    TabuElements setOfTabuElements;
    TabuBundles setOfTabuBundles;
    TabuBundles countTabuBundles;

    std::set<int> usedIds;
    for (auto& snowFlake : temporarySolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        countTabuBundles.push_back(0);
        for (auto elem : snowFlake.ids()) {
            usedIds.insert(elem);
        }
    }

    for (auto i = 0; i< theProblem.getIds().size(); ++i) {
        setOfTabuElements.push_back(0);
    }

    for (auto bundle : temporarySolution) {
        for (auto element : bundle.ids()) {
        }
    }

    maxIter = 1000;
    int iteration = 0;
    SnowFlakeVector bestSolution(temporarySolution.begin(), temporarySolution.end());
    double theBestObjectiveSolution = SnowFlake::objetiveFunction(bestSolution, interSimilarityWeight);

    while (iteration < maxIter) {
        ++iteration;
        this->updateTabuElements(setOfTabuElements);
        this->updateTabuElements(setOfTabuBundles);

        int bundleWithWorstInter = this->findWorstIntraBundle(temporarySolution, setOfTabuBundles);
        if (bundleWithWorstInter == -1) {
            continue;
        }
        SnowFlake originalBundle = temporarySolution.at(bundleWithWorstInter);

        int centroidElement = this->findCentroid(originalBundle, theProblem);

        int farAwayElement = this->findFarAwayElement(centroidElement, originalBundle, theProblem);

        std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, originalBundle,
                                                                 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements);


        double objectiveFunction = SnowFlake::objetiveFunction(temporarySolution, interSimilarityWeight);
        int betterElement;
        bool betterSolution = false;

        int betterWorstElement;
        bool betterWorstSolution = false;
        double bestWorstObjectiveFunction = std::numeric_limits<double>::min();


        for (int aNearestElem : nearestElements) {
            SnowFlake theNewBundle = this->createNewBunlde(originalBundle, farAwayElement, aNearestElem, theProblem);

            temporarySolution[bundleWithWorstInter] = theNewBundle;
            double newObjectiveFunction = SnowFlake::objetiveFunction(temporarySolution, interSimilarityWeight);

            // Si mejora la funcion objetivo
            if (newObjectiveFunction > objectiveFunction) {
                betterSolution = true;
                betterElement = aNearestElem;
            }
            else {
                // No mejora la funcion objetivo pero es mejor que las otras peores y el bundle ya estuvo como tabu
                if (!betterSolution && newObjectiveFunction > bestWorstObjectiveFunction && countTabuBundles.at(theNewBundle.getIdentificator()) > 2) {
                    betterWorstSolution = true;
                    bestWorstObjectiveFunction = newObjectiveFunction;
                    betterWorstElement = aNearestElem;
                }
            }
            temporarySolution[bundleWithWorstInter] = originalBundle;
        }

        if (betterSolution) {
            SnowFlake theBundle = this->createNewBunlde(originalBundle, farAwayElement, betterElement, theProblem);
            temporarySolution[bundleWithWorstInter] = theBundle;
            double tempObjectiveFunction = SnowFlake::objetiveFunction(temporarySolution, interSimilarityWeight);
            if (tempObjectiveFunction > theBestObjectiveSolution) {
                bestSolution.clear();
                bestSolution = temporarySolution;
                theBestObjectiveSolution = tempObjectiveFunction;
            }
            if (farAwayElement != -1) {
                usedIds.erase(farAwayElement);
                setOfTabuElements[farAwayElement] = tabuElementCount;
            }
            usedIds.insert(betterElement);
        }
        else {
            if (betterWorstSolution) {
                SnowFlake theBundle = this->createNewBunlde(originalBundle, farAwayElement, betterWorstElement, theProblem);
                temporarySolution[bundleWithWorstInter] = theBundle;
                if (farAwayElement != -1) {
                    usedIds.erase(farAwayElement);
                    setOfTabuElements[farAwayElement] = tabuElementCount;
                }
                usedIds.insert(betterWorstElement);
            }
            else {
                setOfTabuBundles[bundleWithWorstInter] = tabuBundleCount;
                countTabuBundles[bundleWithWorstInter] = countTabuBundles[bundleWithWorstInter] + 1;
            }
        }
    }
    return bestSolution;
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles) {
    double intraSimilarity = std::numeric_limits<double>::max();
    int worstBundle = -1;
    for (auto snowFlake : vector) {
        if (tabuBundles[snowFlake.getIdentificator()] == 0) {
            double intraCompat = snowFlake.getSumIntraCompat();
            if (intraCompat < intraSimilarity) {
                worstBundle = snowFlake.getIdentificator();
                intraSimilarity = intraCompat;
            }
        }
    }
    return worstBundle;
}

int LocalSearch::findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem) {
    int centroid = -1;
    std::set<int> theIds = worstFlake.ids();
    double maxSumEdges = -1;
    for (auto element : theIds) {
        double sumEdges = 0.0;
        for (auto otherElement : theIds) {
            if (element != otherElement) {
                sumEdges += theProblem.getCompat(element, otherElement);
            }
        }

        if (sumEdges > maxSumEdges) {
            centroid = element;
            maxSumEdges = sumEdges;
        }
    }
    if (centroid == -1) {
        std::stringstream error;
        error<<"No existe centroide. Bundle num: "<<worstFlake.getIdentificator();
        throw Exception(__FILE__, __LINE__,error.str());
    }
    return centroid;
}

int LocalSearch::findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem) {
    int farAwayBundle = -1;
    if (worstFlake.ids().size() == 5) {
        double minSimilarity = std::numeric_limits<double>::max();
        for (auto element : worstFlake.ids()) {
            if (element != centroid) {
                double similarity = theProblem.getCompat(centroid, element);
                if (similarity < minSimilarity) {
                    farAwayBundle = element;
                    minSimilarity = similarity;
                }
            }
        }
    }
    return farAwayBundle;
}

std::vector<int> LocalSearch::nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
                                              IntSet &allElements, std::set<int> &usedElements,
                                              ProblemInstance &theProblem, TabuElements &tabuElements) {
    std::vector<int> nearElements;
    double edgeSimilarity = std::numeric_limits<double>::min();
    double edgeSimilarityTwo = std::numeric_limits<double>::min();
    for (auto element : allElements) {
        if ((usedElements.count(element) == 0) && (tabuElements.at(element) == 0)) {
            bool canReplace = this->checkCoverageConstraint(worstFlake, elementToReplace, element, theProblem);
            if (canReplace) {
                double similarity = theProblem.getCompat(centroid, element);
                if (similarity > edgeSimilarity) {
                    if (similarity > edgeSimilarityTwo) {
                        edgeSimilarityTwo = similarity;
                    }
                    else {
                        edgeSimilarity = similarity;
                    }
                    nearElements.push_back(element);
                }
            }
        }
    }
    return nearElements;
}

SnowFlake LocalSearch::createNewBunlde(SnowFlake worstFlake, int excludeElement, int newElement,
                                       ProblemInstance &theProblem) {

    std::set<int> theNewsId;
    theNewsId.insert(newElement);
    for (auto element : worstFlake.ids()) {
        if (element != excludeElement) {
            theNewsId.insert(element);
        }
    }
    SnowFlake newSnowFlake(theNewsId, &theProblem);
    newSnowFlake.setIdentificator(worstFlake.getIdentificator());
    return newSnowFlake;
}

bool LocalSearch::checkCoverageConstraint(SnowFlake worstFlake, int elementToReplace, int newElement,
                                          ProblemInstance &theProblem) {
    std::set<int> coverageCovered;
    bool ret = true;
    for (auto element : worstFlake.ids()) {
        if (element != elementToReplace) {
            const IntSet* covers = theProblem.getCover(element);
            for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
                if (coverageCovered.count(*cover)!=0) {
                    ret = false;
                }
                coverageCovered.insert(*cover);
            }
        }
    }
    const IntSet* covers = theProblem.getCover(newElement);
    for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
        if (coverageCovered.count(*cover)!=0) {
            ret = false;
        }
        coverageCovered.insert(*cover);
    }
    return ret;
}

void LocalSearch::updateTabuElements(std::vector<int> &tabuSet) {
    for (auto& tabuElement : tabuSet) {
        if (tabuElement > 0) {
            tabuElement--;
        }
    }
}
