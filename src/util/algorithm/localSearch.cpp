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
    SnowFlakeVector finalSolution(solution.begin(), solution.end());
    int id = 0;
    int tabuBundleCount = 10;
    int tabuElementCount = 5;

    TabuElements setOfTabuElements;
    TabuBundles  setOfTabuBundles;

    std::set<int> usedIds;
    for (auto snowFlake : finalSolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        for (auto elem : snowFlake.ids()) {
            usedIds.insert(elem);
        }
    }

    maxIter = 1000;
    int iter = 0;
    while (iter < maxIter) {
        this->updateTabuElements(setOfTabuElements);
        this->updateTabuElements(setOfTabuBundles);
        double objetiveFunction = SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight);
        int bundleWithWorstInter = this->findWorstIntraBundle(finalSolution, setOfTabuBundles);
        if (bundleWithWorstInter == -1) {
            continue;
        }
        SnowFlake originalBundle = finalSolution.at(bundleWithWorstInter);
        int centroidElement = this->findCentroid(originalBundle, theProblem);
        int farAwayElement = this->findFarAwayElement(centroidElement, originalBundle, theProblem);
        std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, originalBundle,
                                                                 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements);
        bool betterSolution = false;
        int selectedElement = -1;
        for (int aNearestElem : nearestElements) {
            SnowFlake theNewBundle = this->createNewBunlde(originalBundle, farAwayElement, aNearestElem, theProblem);
            finalSolution[bundleWithWorstInter] = theNewBundle;
            double newObjetiveFunction = SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight);
            // Si no mejora la funcion objetivo vuelvo atras el cambio
            if (newObjetiveFunction <= objetiveFunction) {
                finalSolution[bundleWithWorstInter] = originalBundle;
                DEBUG(DBG_DEBUG, "\n{\n\ttabu_elemet: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<",\n\t\tid_elemento "<<aNearestElem<<"\n\t}\n}");
                setOfTabuElements[aNearestElem] = tabuElementCount;
            }
            // Si mejora la funcion objetivo
            else {
                betterSolution = true;
                selectedElement = aNearestElem;
            }
        }
        if (betterSolution == true) {
            usedIds.erase(farAwayElement);
            usedIds.insert(selectedElement);
            DEBUG(DBG_DEBUG, "\n{\n\ttabu_elements: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<",\n\t\tid_elemento "<<farAwayElement<<"\n\t}\n}");
            setOfTabuElements[farAwayElement] = tabuElementCount;
        }
        else {
            setOfTabuBundles[bundleWithWorstInter] = tabuBundleCount;
            DEBUG(DBG_DEBUG, "\n{\n\ttabu_bundle: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<"\n\t}\n}");
        }
        ++iter;
    }
    return finalSolution;
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles) {
    double intraSimilarity = std::numeric_limits<double>::max();
    int worstBundle = -1;
    for (auto snowFlake : vector) {
        if (tabuBundles[snowFlake.getIdentificator()] == 0) {
            DEBUG(DBG_DEBUG, "\n{\n\tconsult_bundle: {\n\t\tbundle: "<<snowFlake.getIdentificator()<<"\n\t}\n}");
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
    if (centroid == -1) {
        throw Exception(__FILE__, __LINE__,"no existe un centroide");
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
    if (farAwayBundle == -1) {
        throw Exception(__FILE__, __LINE__,"no existe un elemento lejano");
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
        if ((usedElements.count(element) == 0) && (tabuElements.count(element) == 0)) {
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

void LocalSearch::updateTabuElements(TabuElements &tabuSet) {
    std::set<int> tabuElementsToDelete;
    for (auto& tabuElement : tabuSet) {
        if (tabuElement.second > 0) {
            tabuElement.second--;
        }
        else {
            tabuElementsToDelete.insert(tabuElement.first);
        }
    }
    for (auto elementToDelete : tabuElementsToDelete) {
        tabuSet.erase(elementToDelete);
    }
}

void LocalSearch::updateTabuElements(TabuBundles &tabuSet) {
    for (auto& tabuElement : tabuSet) {
        if (tabuElement > 0) {
            tabuElement--;
        }
    }
}
