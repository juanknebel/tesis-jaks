#include "localSearch.h"
#include "../system/exception.h"
#include "../logger/logger.h"

SnowFlakeVector LocalSearch::execute(int maxIter, const SnowFlakeVector& solution, ProblemInstance& theProblem, Double interSimilarityWeight) {
    /*
     * Tomo un bundle:
     * tomo un elemento y lo intento cambiar por algun otro de los demas bundles
     * si mejora hago efectivo el cambio y paso al siguiente elemento
     * si no mejora intento con otro elemento
     * esto lo repito tantas veces como el parametro de maximas iteraciones
    */
    SnowFlakeVector bestSolution(solution.begin(), solution.end());
    //return bestSolution;
    SnowFlakeVector visitSolution(solution.begin(), solution.end());
    double theBestObjectiveSolution = SnowFlake::objetiveFunction(bestSolution, interSimilarityWeight);
    
    int id = 0;
    int tabuBundleCount = 10;
    int tabuElementCount = 10;

    TabuElements setOfTabuElements;
    TabuBundles setOfTabuBundles;

    std::set<int> usedIds;
    for (auto& snowFlake : visitSolution) {
        snowFlake.setIdentificator(id);
        ++id;
        setOfTabuBundles.push_back(0);
        for (auto elem : snowFlake.ids()) {
            usedIds.insert(elem);
        }
    }

    for (auto i = 0; i< theProblem.getIds().size(); ++i) {
        setOfTabuElements.push_back(0);
    }

    maxIter = 1000;
    int iteration = 0;
    DEBUG(DBG_DEBUG,"max iter: "<<maxIter);
    while (iteration < maxIter) {
        ++iteration;
	
        this->updateTabuElements(setOfTabuElements);
        this->updateTabuElements(setOfTabuBundles);
	
		SnowFlakeVector iterationSolution(visitSolution.begin(), visitSolution.end());

        int bundleWithWorstInter = this->findWorstIntraBundle(iterationSolution, setOfTabuBundles, false);
        if (bundleWithWorstInter == -1) {
            continue;
        }
		
		DEBUG(DBG_DEBUG,"iter num: "<<iteration);
        
        SnowFlake worstBundle = iterationSolution.at(bundleWithWorstInter);
		int centroidElement = this->findCentroid(worstBundle, theProblem);
		int farAwayElement = this->findFarAwayElement(centroidElement, worstBundle, theProblem);
		std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, worstBundle,
                                                                 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements, false);
																
		std::vector<int> nearestElementsNotReplace = this->nearestElements(centroidElement, -1, worstBundle,
                                                                 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements, false);
																 
																				

		int betterElement;
		double itBestObjectiveFunction = -1;
        for (int aNearestElem : nearestElements) {
			SnowFlake theNewBundle = this->createNewBunlde(worstBundle, farAwayElement, aNearestElem, theProblem);
            iterationSolution[bundleWithWorstInter] = theNewBundle;
            double newObjectiveFunction = SnowFlake::objetiveFunction(iterationSolution, interSimilarityWeight);
			if (newObjectiveFunction > itBestObjectiveFunction) {
				itBestObjectiveFunction = newObjectiveFunction;
				betterElement = aNearestElem;
			}
        }
		
		for (int aNearestElem : nearestElementsNotReplace) {
			SnowFlake theNewBundle = this->createNewBunlde(worstBundle, -1, aNearestElem, theProblem);
            iterationSolution[bundleWithWorstInter] = theNewBundle;
            double newObjectiveFunction = SnowFlake::objetiveFunction(iterationSolution, interSimilarityWeight);
			if (newObjectiveFunction > itBestObjectiveFunction) {
				itBestObjectiveFunction = newObjectiveFunction;
				betterElement = aNearestElem;
			}
        }
        
        SnowFlakeVector tabuIterationSolution(visitSolution.begin(), visitSolution.end());
        int tabubundleWithWorstInter = bundleWithWorstInter;
		if (true && tabubundleWithWorstInter > -1) {
			SnowFlake tabuWorstBundle = iterationSolution.at(tabubundleWithWorstInter);
			int tabuCentroidElement = this->findCentroid(tabuWorstBundle, theProblem);
			int tabuFarAwayElement = this->findFarAwayElement(tabuCentroidElement, tabuWorstBundle, theProblem);
			nearestElements = this->nearestElements(tabuCentroidElement, tabuFarAwayElement, tabuWorstBundle,
																	 theProblem.getIds(), usedIds, theProblem,
                                                                 setOfTabuElements, true);
	  
			int tabuBetterElement = -1;
			double tabuItBestObjectiveFunction = itBestObjectiveFunction * 1.2;
			double valueToTakeOffTabuList = itBestObjectiveFunction * 0.9;
			TabuElements elementsToTakeOffTabeList;
			for (int aNearestElem : nearestElements) {
				SnowFlake theNewBundle = this->createNewBunlde(tabuWorstBundle, tabuFarAwayElement, aNearestElem, theProblem);
				tabuIterationSolution[tabubundleWithWorstInter] = theNewBundle;
				double newObjectiveFunction = SnowFlake::objetiveFunction(tabuIterationSolution, interSimilarityWeight);
				if (newObjectiveFunction > tabuItBestObjectiveFunction) {
					tabuItBestObjectiveFunction = newObjectiveFunction;
					tabuBetterElement = aNearestElem;
				}
				else {
				if (newObjectiveFunction > valueToTakeOffTabuList) {
					elementsToTakeOffTabeList.push_back(aNearestElem);
				}
			}
		}
	  
		if (tabuBetterElement > -1){
		  worstBundle = tabuWorstBundle;
		  farAwayElement = tabuFarAwayElement;
		  betterElement = tabuBetterElement;

		}

		for (auto anElement : elementsToTakeOffTabeList) {
		  setOfTabuElements[anElement] = 0;
		}
	}
	
	SnowFlake theBundle = this->createNewBunlde(worstBundle, farAwayElement, betterElement, theProblem);
	visitSolution[bundleWithWorstInter] = theBundle;
	double tempObjectiveFunction = SnowFlake::objetiveFunction(visitSolution, interSimilarityWeight);
	//Actualizo la mejor solucion global
	if (tempObjectiveFunction > theBestObjectiveSolution) {
		bestSolution.clear();
		bestSolution = visitSolution;
		theBestObjectiveSolution = tempObjectiveFunction;
	}
	
	usedIds.erase(farAwayElement);
	usedIds.insert(betterElement);
	setOfTabuElements[farAwayElement] = tabuElementCount;
	setOfTabuBundles[bundleWithWorstInter] = tabuBundleCount;
	  
	
    }
    return bestSolution;
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles, bool takeTabu) {
    double intraSimilarity = std::numeric_limits<double>::max();
    int worstBundle = -1;
    for (auto snowFlake : vector) {
        if(!takeTabu) {
	    if (tabuBundles[snowFlake.getIdentificator()] == 0) {
		double intraCompat = snowFlake.getSumIntraCompat();
		if (intraCompat < intraSimilarity) {
		    worstBundle = snowFlake.getIdentificator();
		    intraSimilarity = intraCompat;
		}
	    }
	}
	else {
	    if (tabuBundles[snowFlake.getIdentificator()] > 0) {
		double intraCompat = snowFlake.getSumIntraCompat();
		if (intraCompat < intraSimilarity) {
		    worstBundle = snowFlake.getIdentificator();
		    intraSimilarity = intraCompat;
		}
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
    //DEBUG(DBG_DEBUG,"Centroide: "<<centroid);
    return centroid;
}

int LocalSearch::findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem) {
    int farAwayBundle = -1;
    if (true) {
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
    //DEBUG(DBG_DEBUG,"Elemento lejano: "<<farAwayBundle);
    return farAwayBundle;
}

std::vector<int> LocalSearch::nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
                                              IntSet &allElements, std::set<int> &usedElements,
                                              ProblemInstance &theProblem, TabuElements &tabuElements, bool takeTabu) {
    int maxElements = 10;
    std::vector<int> nearElements;
    std::vector<double> similarities;
    double minSim = std::numeric_limits<double>::max();
    int minSimPos = -1;
    
    int count=0;
    for (auto element : allElements) {
        if (usedElements.count(element) == 0 && (takeTabu || tabuElements.at(element) == 0)) {
            bool canReplace = this->checkCoverageConstraint(worstFlake, elementToReplace, element, theProblem);
            if (canReplace) {
		double similarity = theProblem.getCompat(centroid, element);
		if (count < maxElements) {
		    nearElements.push_back(element);
		    similarities.push_back(similarity);
		    if(minSim > similarity){
		      minSim = similarity;
		      minSimPos = count;
		    }
		    count++;
		}
		else {
		    if (similarity > minSim) {
		      nearElements[minSimPos] = element;
		      similarities[minSimPos] = similarity;
		      minSim = similarity;
		      for(int i = 0; i<similarities.size(); i++) {
			if(minSim > similarities[i]) {
			  minSim = similarities[i];
			  minSimPos = i;
			}
		      }
		    }
		}
            }
        }
    }
    //DEBUG(DBG_DEBUG,"Cantiad de elementos cercanos: "<<nearElements.size());
    //DEBUG(DBG_DEBUG,"Cantidad de replace: "<<c);
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
            const IntSet *covers = theProblem.getCover(element);
            for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
                if (coverageCovered.count(*cover) != 0) {
                    ret = false;
                }
                coverageCovered.insert(*cover);
            }
        }
    }
    const IntSet *covers = theProblem.getCover(newElement);
    for (IntSet::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
        if (coverageCovered.count(*cover) != 0) {
            ret = false;
        }
        coverageCovered.insert(*cover);
    }
    bool checkBudget;
    if (elementToReplace != -1) {
        checkBudget = (worstFlake.getCost() - theProblem.getCost(elementToReplace) + theProblem.getCost(newElement)) <=
                      theProblem.getbudget();
    }
    else {
        checkBudget = (worstFlake.getCost() + theProblem.getCost(newElement)) <= theProblem.getbudget();
    }
    return ret && checkBudget;
}

void LocalSearch::updateTabuElements(std::vector<int> &tabuSet) {
    for (auto& tabuElement : tabuSet) {
        if (tabuElement > 0) {
            tabuElement--;
        }
    }
}
