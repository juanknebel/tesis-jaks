#include "localSearch.h"
#include "../system/exception.h"
#include "../logger/simpleLogger.h"
/*#include "../writer/writterSolutionFile.h"
#include "../writer/writerSolutionArticles.h"*/

void logToFile(int iteration, int bundleWithWorstInter, int centroidElement, int farAwayElement, int theIdOfTheChoosenElement, double objetiveFunction, SnowFlake theSnowflake)
{
    LOG_DEBUG<<iteration<<"\t"<<bundleWithWorstInter<<"\t"<<centroidElement<<"\t"<<farAwayElement<<"\t"<<theIdOfTheChoosenElement<<"\t"<<objetiveFunction<<"\t"<<theSnowflake;
}

SnowFlakeVector LocalSearch::execute(int maxIter, const SnowFlakeVector& solution, ProblemInstance& theProblem, double interSimilarityWeight)
{
	/*
	* Tomo un bundle:
	* tomo un elemento y lo intento cambiar por algun otro de los demas bundles
	* si mejora hago efectivo el cambio y paso al siguiente elemento
	* si no mejora intento con otro elemento
	* esto lo repito tantas veces como el parametro de maximas iteraciones
	*/
	SnowFlakeVector bestSolution(solution.begin(), solution.end());
	SnowFlakeVector visitSolution(solution.begin(), solution.end());
	std::set<int> lonleyElements;
    std::vector<int> centroidTimes;
	double theBestObjectiveSolution = SnowFlake::objetiveFunction(bestSolution, interSimilarityWeight);

    maxIter = 1001;
	int id = 0;
	int tabuBundleCount = solution.size();
	int tabuElementCount = 2*maxIter/tabuBundleCount;

	TabuBundles setOfTabuBundles;
	std::map<int, std::set<int>> mapOfTabus;
	std::map<int, int> recentlyAdded;
	std::set<int> usedIds;
	TabuElements setOfTabuElements;

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
        centroidTimes.push_back(0);
	}

	maxIter = 1001;
	int iteration = 0;

	//LOG_DEBUG<<"FnObjetivoInicial\t"<<theBestObjectiveSolution<<"\n";
    //LOG_DEBUG<<"Iteracion\tBundle con peor Inter\tElemento centroide\tElemento lejano\tElemento elegido\tNueva funcion objetivo\tEl nuevo snowflake";
	while (iteration < maxIter) {
		++iteration;
		this->updateTabuElements(setOfTabuElements);
		this->updateTabuElements(setOfTabuBundles);
		SnowFlakeVector iterationSolution(visitSolution.begin(), visitSolution.end());
		int bundleWithWorstInter = this->findWorstIntraBundle(iterationSolution, setOfTabuBundles, false);
		if (bundleWithWorstInter == -1) {
			continue;
		}
		SnowFlake worstBundle = iterationSolution.at(bundleWithWorstInter);
		int centroidElement = this->findCentroid(worstBundle, theProblem, centroidTimes);
        centroidTimes[centroidElement] = centroidTimes[centroidElement] + 1;
		int farAwayElement = this->findFarAwayElement(centroidElement, worstBundle, theProblem, recentlyAdded);

		SnowFlakeWithChooseElement bundleWithOneRandomMoreElement = this->addOneRandomElementToBundle(worstBundle,
                                                                                                      theProblem,
                                                                                                      usedIds,
                                                                                                      setOfTabuElements,
                                                                                                      visitSolution,
                                                                                                      interSimilarityWeight,
                                                                                                      centroidElement);
        SnowFlakeWithChooseElement bundleWithFarAwayElementReplace = this->replaceFarAwayElementInBundle(worstBundle,
                                                                                                         centroidElement,
                                                                                                         farAwayElement,
                                                                                                         theProblem.getIds(),
                                                                                                         usedIds,
                                                                                                         theProblem,
                                                                                                         setOfTabuElements,
                                                                                                         false,
                                                                                                         mapOfTabus,
                                                                                                         bundleWithWorstInter,
                                                                                                         iterationSolution,
                                                                                                         interSimilarityWeight,
                                                                                                         visitSolution, theBestObjectiveSolution);
        SnowFlakeWithChooseElement bundleWithoutFarAwayElement = this->removeFarAwayElement(worstBundle, farAwayElement,
																							theProblem, visitSolution,
																							interSimilarityWeight);

		LocalSearch::SnowFlakeWithChooseElement bundleAndElementNotTabu;


        if (bundleWithoutFarAwayElement.theSnowflake.ids().size() == 1 && lonleyElements.count(centroidElement) &&
            farAwayElement != -1) {
            bundleAndElementNotTabu.theSnowflake = this->createNewBunlde(worstBundle, centroidElement,
                                                                         farAwayElement, theProblem);
            bundleAndElementNotTabu.theIdOfTheChoosenElement = centroidElement;
            visitSolution[bundleWithWorstInter] = bundleAndElementNotTabu.theSnowflake;
            bundleAndElementNotTabu.objetiveFunction = SnowFlake::objetiveFunction(visitSolution, interSimilarityWeight);
        }
        else {
            bundleAndElementNotTabu = std::max(bundleWithoutFarAwayElement, std::max(bundleWithOneRandomMoreElement, bundleWithFarAwayElementReplace));
        }

        SnowFlakeWithChooseElement bundleWithOneRandomMoreElementTabu = this->addOneRandomElementToBundle(worstBundle,
                                                                                                      theProblem,
                                                                                                      usedIds,
                                                                                                      setOfTabuElements,
                                                                                                      visitSolution,
                                                                                                      interSimilarityWeight,
                                                                                                      centroidElement);
        SnowFlakeWithChooseElement bundleWithFarAwayElementReplaceTabu = this->replaceFarAwayElementInBundle(worstBundle,
                                                                                                         centroidElement,
                                                                                                         farAwayElement,
                                                                                                         theProblem.getIds(),
                                                                                                         usedIds,
                                                                                                         theProblem,
                                                                                                         setOfTabuElements,
                                                                                                         true,
                                                                                                         mapOfTabus,
                                                                                                         bundleWithWorstInter,
                                                                                                         iterationSolution,
                                                                                                         interSimilarityWeight,
                                                                                                         visitSolution, bundleAndElementNotTabu.objetiveFunction);

        LocalSearch::SnowFlakeWithChooseElement bundleAndElementTabu = std::max(bundleWithOneRandomMoreElementTabu, bundleWithFarAwayElementReplaceTabu);

        //LocalSearch::SnowFlakeWithChooseElement bundleAndElement = std::max(bundleAndElementNotTabu, bundleAndElementTabu);
        LocalSearch::SnowFlakeWithChooseElement bundleAndElement = bundleAndElementNotTabu;
        //LocalSearch::SnowFlakeWithChooseElement bundleAndElement = bundleAndElementTabu;

        //logToFile(iteration, bundleWithWorstInter, centroidElement, farAwayElement, bundleAndElement.theIdOfTheChoosenElement, bundleAndElement.objetiveFunction, bundleAndElement.theSnowflake);

        //Actualizo la mejor solucion global
		if (bundleAndElement.objetiveFunction > theBestObjectiveSolution) {
			bestSolution = SnowFlakeVector();
			bestSolution = visitSolution;
            bestSolution[bundleWithWorstInter] = bundleAndElement.theSnowflake;
			theBestObjectiveSolution = bundleAndElement.objetiveFunction;
		}
		if (farAwayElement != -1) {
            usedIds.erase(farAwayElement);
            setOfTabuElements[farAwayElement] = tabuElementCount;
        }
        if (bundleAndElement.theIdOfTheChoosenElement != -1) {
            usedIds.insert(bundleAndElement.theIdOfTheChoosenElement);
            recentlyAdded[bundleAndElement.theIdOfTheChoosenElement] = 3;
            if (farAwayElement != -1) {
                std::set<int> theSet(mapOfTabus[farAwayElement]);
                theSet.insert(bundleAndElement.theIdOfTheChoosenElement);
                mapOfTabus[farAwayElement] = theSet;
            }
        }
		setOfTabuBundles[bundleWithWorstInter] = tabuBundleCount;
        //LOG_DEBUG<<"bundle worst "<<worstBundle;
		for (auto element : worstBundle.ids()) {
			if (recentlyAdded.find(element) != recentlyAdded.end() && recentlyAdded[element] > 0) {
				recentlyAdded[element]--;
			}
		}
		visitSolution[bundleWithWorstInter] = bundleAndElement.theSnowflake;
		if (bundleAndElement.theSnowflake.ids().size() == 1) {
			lonleyElements.insert((int) *bundleAndElement.theSnowflake.ids().begin());
		}
	}
	return bestSolution;
}

int LocalSearch::findWorstIntraBundle(SnowFlakeVector &vector, TabuBundles &tabuBundles, bool takeTabu)
{
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

int LocalSearch::findCentroid(SnowFlake worstFlake, ProblemInstance &theProblem, std::vector<int>& centroidTimes)
{
	int centroid = -1;
    int centroid2 = -1;
	std::set<int> theIds(worstFlake.ids());
	std::set<int> theIds2(worstFlake.ids());
	double maxSumEdges = -1;
    double maxSumEdges2 = -1;

	for (int element : theIds) {
		double sumEdges = 0.0;
		for (int otherElement : theIds2) {
			if (element != otherElement) {
				sumEdges += theProblem.getCompat(element, otherElement);
			}
		}

		if (sumEdges > maxSumEdges) {
			centroid = element;
			maxSumEdges = sumEdges;
		}

        if (sumEdges > maxSumEdges2 && centroidTimes[element] < 3) {
			centroid2 = element;
			maxSumEdges2 = sumEdges;
		}
	}

    if(centroid2 > -1){
        return centroid2;
    }

	if (centroid == -1) {
		std::stringstream error;
		error<<"No existe centroide. Bundle num: "<<worstFlake.getIdentificator();
		throw Exception(__FILE__, __LINE__,error.str());
	}

	return centroid;
}

int LocalSearch::findFarAwayElement(int centroid, SnowFlake worstFlake, ProblemInstance &theProblem, std::map<int,int> recentlyAdded)
{
	int farAwayBundle = -1;
	int farAwayBundleNotTabu = -1;

	if (true) {
		double minSimilarity = std::numeric_limits<double>::max();
		double minSimilarityNotTabu = std::numeric_limits<double>::max();

		for (auto element : worstFlake.ids()) {
			if (element != centroid) {
				double similarity = theProblem.getCompat(centroid, element);
				if(recentlyAdded.find(element) != recentlyAdded.end() && recentlyAdded[element]>0){
					if (similarity < minSimilarityNotTabu) {
						farAwayBundleNotTabu = element;
						minSimilarityNotTabu = similarity;
					}
				}
				else{
					if (similarity < minSimilarity) {
						farAwayBundle = element;
						minSimilarity = similarity;
					}
				}
			}
		}
	}

	if (farAwayBundleNotTabu > -1){
		return farAwayBundleNotTabu;
	}
	else{
		return farAwayBundle;
	}
}

std::vector<int> LocalSearch::nearestElements(int centroid, int elementToReplace, SnowFlake worstFlake,
        std::set<int> &allElements, std::set<int> &usedElements,
        ProblemInstance &theProblem, std::vector<int> &tabuElements, bool takeTabu, std::map<int, std::set<int>> mapOfTabus)
{
	int maxElements = 10;
	std::vector<int> nearElements;
	std::vector<double> similarities;
	double minSim = std::numeric_limits<double>::max();
	int minSimPos = -1;

	int count=0;

	for (auto element : allElements) {
		if (usedElements.count(element) == 0 && (takeTabu || tabuElements.at(element) == 0)) {
			bool canReplace = this->checkCoverageConstraint(worstFlake, elementToReplace, element, theProblem);
			std::set<int> theSet(mapOfTabus[elementToReplace]);
			bool isInTabuMovement = theSet.count(element) != 0;
			if (canReplace && !isInTabuMovement) {
				double similarity = theProblem.getCompat(centroid, element);

				if (count < maxElements) {
					nearElements.push_back(element);
					similarities.push_back(similarity);

					if(minSim > similarity) {
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

	return nearElements;
}

SnowFlake LocalSearch::createNewBunlde(SnowFlake worstFlake, int excludeElement, int newElement,
                                       ProblemInstance &theProblem)
{

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
        ProblemInstance &theProblem)
{
	std::set<int> coverageCovered;
	bool ret = true;

	for (auto element : worstFlake.ids()) {
		if (element != elementToReplace) {
			const std::set<int> *covers = theProblem.getCover(element);

			for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
				if (coverageCovered.count(*cover) != 0) {
					ret = false;
				}

				coverageCovered.insert(*cover);
			}
		}
	}

	const std::set<int> *covers = theProblem.getCover(newElement);

	for (std::set<int>::iterator cover = covers->begin(); cover != covers->end(); ++cover) {
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

void LocalSearch::updateTabuElements(std::vector<int> &tabuSet)
{
	for (int i = 0; i < tabuSet.size(); ++i) {
		if (tabuSet[i] > 0) {
			tabuSet[i] = tabuSet[i] - 1;
		}
	}
}

LocalSearch::SnowFlakeWithChooseElement LocalSearch::addOneRandomElementToBundle(SnowFlake bundle, ProblemInstance &theProblem, std::set<int> setOfUsedElements,
                                                                    TabuElements setOfTabuElements, SnowFlakeVector visitedSolution,
                                                                    double interSimilarityWeight, int centroid) {
    srand(1);
    int randomElement = -1;
    double maxSimilarity = -1;
    for (int anElement : theProblem.getIds()) {
        bool findOne = setOfTabuElements[anElement] == 0 && setOfUsedElements.count(anElement) == 0 &&
                this->checkCoverageConstraint(bundle, -1, anElement, theProblem);
        if (findOne) {
            double similarity = theProblem.getCompat(centroid, anElement);
            if (similarity > maxSimilarity) {
                randomElement = anElement;
                maxSimilarity = similarity;
            }
        }
    }

    LocalSearch::SnowFlakeWithChooseElement bundleAndElement;
    if (randomElement == -1) {
        bundleAndElement.theSnowflake = bundle;
        bundleAndElement.theIdOfTheChoosenElement = -1;
        bundleAndElement.objetiveFunction = -1;
    }
    else {
        bundleAndElement.theSnowflake = this->createNewBunlde(bundle, -1, randomElement, theProblem);
        visitedSolution[bundle.getIdentificator()] = bundleAndElement.theSnowflake;
        bundleAndElement.theIdOfTheChoosenElement = randomElement;
        bundleAndElement.objetiveFunction = SnowFlake::objetiveFunction(visitedSolution, interSimilarityWeight);
    }

    return bundleAndElement;
}

LocalSearch::SnowFlakeWithChooseElement
LocalSearch::replaceFarAwayElementInBundle(SnowFlake bundle, int centroidElement, int farAwayElement, std::set<int> &setOfElements,
                                           std::set<int> setOfUsedElements, ProblemInstance &theProblem,
                                           TabuElements setOfTabuElements, bool takeTabu, std::map<int, std::set<int>> mapOfTabus,
                                           int bundleWithWorstInter, SnowFlakeVector iterationSolution, double interSimilarityWeight,
                                           SnowFlakeVector visitedSolution, double theBestObjectiveSolution) {
    LocalSearch::SnowFlakeWithChooseElement bundleAndElement;
    if (farAwayElement == -1) {
        bundleAndElement.theIdOfTheChoosenElement = -1;
        bundleAndElement.theSnowflake = bundle;
        bundleAndElement.objetiveFunction = -1;
    }
    else {
        if (!takeTabu) {
            std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, bundle,
                                                                     theProblem.getIds(), setOfUsedElements, theProblem,
                                                                     setOfTabuElements, takeTabu, mapOfTabus);

            int betterElement;
            double itBestObjectiveFunction = -1;

            for (int aNearestElem : nearestElements) {
                SnowFlake theNewBundle = this->createNewBunlde(bundle, farAwayElement, aNearestElem, theProblem);
                iterationSolution[bundleWithWorstInter] = theNewBundle;
                double newObjectiveFunction = SnowFlake::objetiveFunction(iterationSolution, interSimilarityWeight);

                if (newObjectiveFunction > itBestObjectiveFunction) {
                    itBestObjectiveFunction = newObjectiveFunction;
                    betterElement = aNearestElem;
                }
            }
            SnowFlake theBundle = this->createNewBunlde(bundle, farAwayElement, betterElement, theProblem);
            visitedSolution[bundle.getIdentificator()] = theBundle;
            bundleAndElement.theIdOfTheChoosenElement = betterElement;
            bundleAndElement.theSnowflake = theBundle;
            bundleAndElement.objetiveFunction = SnowFlake::objetiveFunction(visitedSolution, interSimilarityWeight);
        }
        else {
            std::vector<int> nearestElements = this->nearestElements(centroidElement, farAwayElement, bundle,
                                                theProblem.getIds(), setOfUsedElements, theProblem, setOfTabuElements, true, mapOfTabus);

            int tabuBetterElement = -1;
            double tabuItBestObjectiveFunction = theBestObjectiveSolution * 1.01;
            double valueToTakeOffTabuList = theBestObjectiveSolution * 1.1;
            TabuElements elementsToTakeOffTabeList;

            for (int aNearestElem : nearestElements) {
                SnowFlake theNewBundle = this->createNewBunlde(bundle, farAwayElement, aNearestElem, theProblem);
                iterationSolution[bundleWithWorstInter] = theNewBundle;
                double newObjectiveFunction = SnowFlake::objetiveFunction(iterationSolution, interSimilarityWeight);

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

            if (tabuBetterElement > -1) {
                SnowFlake theBundle = this->createNewBunlde(bundle, farAwayElement, tabuBetterElement, theProblem);
                visitedSolution[bundle.getIdentificator()] = theBundle;
                bundleAndElement.theIdOfTheChoosenElement = tabuBetterElement;
                bundleAndElement.theSnowflake = theBundle;
                bundleAndElement.objetiveFunction = SnowFlake::objetiveFunction(visitedSolution, interSimilarityWeight);
            }
            else {
                bundleAndElement.theIdOfTheChoosenElement = -1;
                bundleAndElement.theSnowflake = bundle;
                bundleAndElement.objetiveFunction = -1;
            }

            for (auto anElement : elementsToTakeOffTabeList) {
                //setOfTabuElements[anElement] = 0;
            }
        }
    }
    return bundleAndElement;
}

LocalSearch::SnowFlakeWithChooseElement LocalSearch::removeFarAwayElement(SnowFlake bundle, int farAwayElement, ProblemInstance &theProblem,
															 SnowFlakeVector visitedSolution, double interSimilarityWeight) {
    LocalSearch::SnowFlakeWithChooseElement bundleAndElement;
    if (farAwayElement == -1) {
        bundleAndElement.theSnowflake = bundle;
        bundleAndElement.theIdOfTheChoosenElement = -1;
        bundleAndElement.objetiveFunction = -1;
    }
    else {
        std::set<int> theNewsId;
        for (auto element : bundle.ids()) {
            if (element != farAwayElement) {
                theNewsId.insert(element);
            }
        }

        SnowFlake newSnowFlake(theNewsId, &theProblem);
        newSnowFlake.setIdentificator(bundle.getIdentificator());
        visitedSolution[bundle.getIdentificator()] = newSnowFlake;
        bundleAndElement.theSnowflake = newSnowFlake;
        bundleAndElement.theIdOfTheChoosenElement = farAwayElement;
        bundleAndElement.objetiveFunction = SnowFlake::objetiveFunction(visitedSolution, interSimilarityWeight);
    }
    return bundleAndElement;
}
