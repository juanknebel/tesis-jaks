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
    SnowFlakeVector tempSolution;
    int id = 0;
    int tabuBundleCount = 10;
    int tabuElementCount = 5;

    TabuElements setOfTabuElements;
    TabuBundles setOfTabuBundles;
    TabuBundles countTabuBundles;

    std::set<int> usedIds;
    for (auto& snowFlake : finalSolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        countTabuBundles.push_back(0);
        for (auto elem : snowFlake.ids()) {
            usedIds.insert(elem);
        }
    }

    for (auto element : theProblem.getIds()) {
        setOfTabuElements.push_back(0);
    }

    //DEBUG(DBG_DEBUG,"Solution inicial\n");
    for (auto bundle : finalSolution) {
        //DEBUG(DBG_DEBUG,"Bundle: " << bundle.getIdentificator() << "\n");
        for (auto element : bundle.ids()) {
            //DEBUG(DBG_DEBUG,"Elemento: " << element << "\n");
        }
    }
    //DEBUG(DBG_DEBUG,"Fin Solution inicial\n");

    maxIter = 100;
    int iter = 0;
    while (iter < maxIter) {
        ++iter;
        //DEBUG(DBG_DEBUG, "Inicio Iteracion: "<<iter<<"\n");
        this->updateTabuElements(setOfTabuElements);
        this->updateTabuElements(setOfTabuBundles);
        double objetiveFunction = SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight);
        int bundleWithWorstInter = this->findWorstIntraBundle(finalSolution, setOfTabuBundles);
        if (bundleWithWorstInter == -1) {
            continue;
        }
        SnowFlake originalBundle = finalSolution.at(bundleWithWorstInter);
        //DEBUG(DBG_DEBUG, "Bundle elegido: "<<originalBundle.getIdentificator()<<"\n");
        int centroidElement = this->findCentroid(originalBundle, theProblem);
        if (centroidElement == -1) {
            continue;
        }
        int farAwayElement = this->findFarAwayElement(centroidElement, originalBundle, theProblem);
        if (farAwayElement == -1) {
            setOfTabuBundles[bundleWithWorstInter] = maxIter;
            continue;
        }
        std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, originalBundle,
                                                                 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements);
        bool betterSolution = false;
        int selectedElement = -1;
        int betterWorstElement = -1;
        bool betterWorstSolution = false;
        double bestNewObjetiveFunction = std::numeric_limits<double>::min();
        for (int aNearestElem : nearestElements) {
            //DEBUG(DBG_DEBUG, "Elemento cercano: "<<aNearestElem<<"\n");
            SnowFlake theNewBundle = this->createNewBunlde(originalBundle, farAwayElement, aNearestElem, theProblem);
            finalSolution[bundleWithWorstInter] = theNewBundle;
            double newObjetiveFunction = SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight);
            // Si no mejora la funcion objetivo vuelvo atras el cambio
            if (newObjetiveFunction <= objetiveFunction) {
                if (newObjetiveFunction > bestNewObjetiveFunction && countTabuBundles.at(bundleWithWorstInter) >= 1) {
                    bestNewObjetiveFunction = newObjetiveFunction;
                    betterWorstElement = aNearestElem;
                    betterWorstSolution = true;
                    DEBUG(DBG_DEBUG, "Pero funcion objetivo: "<<bestNewObjetiveFunction<<"\n");
                }
                finalSolution[bundleWithWorstInter] = originalBundle;
                //DEBUG(DBG_DEBUG, "\n{\n\ttabu_elemet: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<",\n\t\tid_elemento "<<aNearestElem<<"\n\t}\n}");
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
            //DEBUG(DBG_DEBUG, "Elemento seleccionado: "<<selectedElement<<"\n");
            //DEBUG(DBG_DEBUG, "Elemento Eliminado: "<<farAwayElement<<"\n");
            //DEBUG(DBG_DEBUG, "\n{\n\ttabu_elements: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<",\n\t\tid_elemento "<<farAwayElement<<"\n\t}\n}");
            setOfTabuElements[farAwayElement] = tabuElementCount;
        }
        else {
            if (betterWorstSolution == true) {
                SnowFlake theNewBundle = this->createNewBunlde(originalBundle, farAwayElement, betterWorstElement, theProblem);
                if (tempSolution.size() == 0) {
                    tempSolution = finalSolution;
                }
                else {
                    if (bestNewObjetiveFunction > SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight)) {
                        tempSolution.clear();
                        tempSolution = finalSolution;
                    }
                }
                finalSolution[bundleWithWorstInter] = theNewBundle;
                setOfTabuElements[farAwayElement] = tabuElementCount;
            }
            setOfTabuBundles[bundleWithWorstInter] = tabuBundleCount;
            countTabuBundles[bundleWithWorstInter] = countTabuBundles[bundleWithWorstInter] + 1;
            //DEBUG(DBG_DEBUG, "\n{\n\ttabu_bundle: {\n\t\titeracion: "<<iter<<",\n\t\tbundle: "<<bundleWithWorstInter<<"\n\t}\n}");
        }
        //DEBUG(DBG_DEBUG, "Fin Iteracion: "<<iter<<"\n");
    }

    if (SnowFlake::objetiveFunction(finalSolution, interSimilarityWeight) > SnowFlake::objetiveFunction(tempSolution, interSimilarityWeight)) {
        return finalSolution;
    }
    else {
        return tempSolution;
    }
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles) {
    double intraSimilarity = std::numeric_limits<double>::max();
    int worstBundle = -1;
    for (auto snowFlake : vector) {
        if (tabuBundles[snowFlake.getIdentificator()] == 0) {
            //DEBUG(DBG_DEBUG, "\n{\n\tconsult_bundle: {\n\t\tbundle: "<<snowFlake.getIdentificator()<<"\n\t}\n}");
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
        //DEBUG(DBG_DEBUG, "\n{\n\tconsult_centroid: {\n\t\tbundle: "<<worstFlake.getIdentificator()<<",\n\t\tmax_local: "<<sumEdges<<",\n\t\tmax_global "<<maxSumEdges<<"\n\t}\n}");
        if (sumEdges > maxSumEdges) {
            centroid = element;
            maxSumEdges = sumEdges;
        }
    }
    if (centroid == -1) {
        //throw Exception(__FILE__, __LINE__,"no existe un centroide");
    }
    return centroid;
}

int LocalSearch::findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem) {
    int farAwayBundle = -1;
    double minSimilarity = std::numeric_limits<double>::max();
    //DEBUG(DBG_DEBUG, "Centroide: "<<centroid<<"\n");
    //DEBUG(DBG_DEBUG, "--------------\nMaximo"<<minSimilarity<<"\n--------------\n");
    for (auto element : worstFlake.ids()) {
        if (element != centroid) {
            double similarity = theProblem.getCompat(centroid, element);
            //DEBUG(DBG_DEBUG, "Elemento: "<<element<<"\n");
            //DEBUG(DBG_DEBUG, "Compatibilidad entre centroide y elemento: "<<centroid<<", "<<element<<"="<<similarity<<"\n");
            if (similarity < minSimilarity) {
                farAwayBundle = element;
                minSimilarity = similarity;
            }
        }
    }
    if (farAwayBundle == -1) {
        //throw Exception(__FILE__, __LINE__,"no existe un elemento lejano");
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

void LocalSearch::updateTabuElements(TabuBundles &tabuSet) {
    for (auto& tabuElement : tabuSet) {
        if (tabuElement > 0) {
            tabuElement--;
        }
    }
}
