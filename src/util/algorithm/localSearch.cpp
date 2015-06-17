#include "localSearch.h"

SnowFlakeVector LocalSearch::execute(int maxIter, SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight) {
    /*
     * Tomo un bundle:
     * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
     * si mejora hago efectivo el cambio y paso al siguiente elemento
     * si no mejora intento con otro elemento
     * esto lo repito tantas veces como el parametro de maximas iteraciones
    */
    SnowFlakeVector finalSolution;
    int id = 0;
    int maxBetter = 5;
    int tabuCount = 5;

    std::vector<LocalSearch::UsedElements> vectorOfUsedFlakes;

    std::set<int> usedIds;
    for (auto snowFlake : solution) {
        snowFlake.setIdentificator(id);
        ++id;
        vectorOfUsedFlakes.push_back(LocalSearch::UsedElements {int(snowFlake.getIdentificator()),maxBetter, tabuCount});
        for (auto elem : snowFlake.ids()) {
            usedIds.insert(elem);
        }
    }

    maxIter = 100;
    int iter = 0;
    while (iter < maxIter) {
        double objetiveFunction = SnowFlake::objetiveFunction(solution, interSimilarityWeight);
        int bundleWithWorstInter = this->findWorstIntraBundle(solution);
        SnowFlake originalBundle = solution.at(bundleWithWorstInter);
        int centroidElement = this->findCentroid(originalBundle, theProblem);
        int farAwayElement = this->findFarAwayElement(centroidElement, originalBundle, theProblem);
        std::vector<int> nearestElements = this->nearestElements(centroidElement, originalBundle, theProblem.getIds(),
                                                                 usedIds, theProblem);
        for (auto elem : nearestElements) {
            SnowFlake theNewBundle = this->createNewBunlde(originalBundle, elem);
            solution[bundleWithWorstInter] = theNewBundle;
        }
        ++iter;
    }

    return finalSolution;
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector) {
    double intraSimilarity = std::numeric_limits<double>::max();
    int worstBundle = -1;
    for (auto snowFlake : vector) {
        double intraCompat = snowFlake.getSumIntraCompat();
        if (intraCompat < intraSimilarity) {
            worstBundle = snowFlake.getIdentificator();
            intraSimilarity = intraCompat;
        }
    }
    return worstBundle;
}

int LocalSearch::findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem) {
    int centroid = -1;
    std::set<int> theIds = worstFlake.ids();
    double maxSumEdges = std::numeric_limits<double>::min();
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
    return centroid;
}

int LocalSearch::findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem) {
    int farAwayBundle = -1;
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
    return farAwayBundle;
}

std::vector<int> LocalSearch::nearestElements(int centroid, SnowFlake worstFlake, IntSet &allElements,
                                              std::set<int> &usedElements, ProblemInstance &theProblem) {
    std::vector<int> nearElements;
    double edgeSimilarity = std::numeric_limits<double>::min();
    double edgeSimilarityTwo = std::numeric_limits<double>::min();
    for (auto element : allElements) {
        if (usedElements.count(element) == 0) {
            bool canReplace = this->checkCoverageConstraint(worstFlake, centroid, element, theProblem);
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

SnowFlake LocalSearch::createNewBunlde(SnowFlake worstFlake, int anElement, ProblemInstance &theProblem) {
    SnowFlake newSnowFlake;

    return newSnowFlake;
}

bool LocalSearch::checkCoverageConstraint(SnowFlake worstFlake, int centroid, const int newElement,
                                          ProblemInstance &theProblem) {
    return false;
}
