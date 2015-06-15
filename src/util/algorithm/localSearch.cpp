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
        snowFlake->setIdentificator(id);
        ++id;
        vectorOfUsedFlakes.push_back(LocalSearch::UsedElements {int(snowFlake->getIdentificator()),maxBetter, tabuCount});
        for (auto elem : snowFlake->ids()) {
            usedIds.insert(elem);
        }
    }

    maxIter = 100;
    int iter = 0;
    while (iter < maxIter) {
        double objetiveFunction = SnowFlake::objetiveFunction(solution, interSimilarityWeight);
        int bundleWithWorstInter = this->findWorstInterBundle(solution);
        SnowFlake* originalBundle = solution.at(bundleWithWorstInter);
        int centroidElement = this->findCentroid(originalBundle);
        int farAwayElement = this->findFarAwayElement(centroidElement, originalBundle);
        std::vector<int> nearestElements = this->nearestElements(centroidElement, originalBundle, theProblem.getIds(), usedIds);
        for (auto elem : nearestElements) {
            SnowFlake* theNewBundle = this->createNewBunlde(originalBundle, elem);
            solution[bundleWithWorstInter] = theNewBundle;
        }
        ++iter;
    }

    return finalSolution;
}

