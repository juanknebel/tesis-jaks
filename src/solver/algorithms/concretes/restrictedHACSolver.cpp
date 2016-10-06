/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"
#include "../../../problem/factoryFlake.h"
#include <map>

RestrictedHACSolver::~RestrictedHACSolver()
{
}

//ESTA ES LA IMPLEMENTACION VIEJA
std::vector<SnowFlake> RestrictedHACSolver::produceManySnowflakes(int numToProduce, ProblemInstance &theProblem)
{
	if (theProblem.numNodes() < numToProduce) {
		throw Exception(__FILE__, __LINE__, "IllegalArgumentException Too few nodes");
	}

	// Put each item in its own cluster
	std::map<int, std::set<Flake>> clustering;
	int totalElements = theProblem.numNodes();

	matrix<std::pair<double, bool>> *theMatrixC = new matrix<std::pair<double, bool>> (totalElements, totalElements);
	std::vector<int> theIVector;
	std::vector<std::pair<int, double>> nbm;
	double tempMaxSimilarity, similarity;
	int tempMaxIndex;

	//Inicializo el cluster, la matriz con las similitudes, vector de indices y nbm
	for (int i = 0; i < totalElements; ++i) {
		//init del clustering
		Flake theFlakeI = FactoryFlake::createNewFlake(i, theProblem);
		std::set<Flake> temp = std::set<Flake>();
		temp.insert(theFlakeI);
		clustering[i] = temp;
		//init de matriz y vectores
		tempMaxSimilarity = -1.00;
		tempMaxIndex = -1;

		for (int j = 0; j < totalElements; ++j) {
			if(i == j) {
				continue;
			}
			Flake theFlakeJ = FactoryFlake::createNewFlake(j, theProblem);
			//similarity = this->problem_->getCompatWithSpecificProfile(i, j);//ESTA LINEA HAY QUE CAMBIAR
			similarity = Flake::getCompat(theFlakeI, theFlakeJ, theProblem);
			std::set<Flake> aSetWithElementI = std::set<Flake>();
			aSetWithElementI.insert(theFlakeI);
			std::set<Flake> aSetWithElementJ = std::set<Flake>();
			aSetWithElementJ.insert(theFlakeJ);
			bool canMergeIandJ = this->checkBudgetAndCoverageConstraint(aSetWithElementI, aSetWithElementJ,
																		theProblem);

			if (similarity > tempMaxSimilarity && canMergeIandJ) {
				tempMaxIndex = j;
				tempMaxSimilarity = similarity;
			}

			theMatrixC->insert_element(i, j, std::pair<double, bool>(similarity, canMergeIandJ));
		}

		theIVector.push_back(i);
		std::pair<int, double> theMaxValue (tempMaxIndex, tempMaxSimilarity);
		nbm.push_back(theMaxValue);
	}

	//Empiezo a intentar clusterizar
	int j = 0;

	while (j < totalElements - 1 && clustering.size() > numToProduce) {
		tempMaxSimilarity = -1.00;
		tempMaxSimilarity = -1.00;
		int anElementi1, otherElementi2;

		//Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento
		for (int k = 0; k < totalElements; ++k) {
			std::pair<int, double> aTupleToCompare = nbm.at(k);

			if (std::get<1>(aTupleToCompare) > tempMaxSimilarity && k == theIVector.at(k)) {
				anElementi1 = k;
				tempMaxSimilarity = std::get<1>(aTupleToCompare);
			}
		}

		if (tempMaxSimilarity == -1.00) {
			break;
		}

		//busco recursivamente el segundo elemento
		int theIndex = std::get<0>(nbm.at(anElementi1));
		bool notIndex = true;

		while (notIndex == true) {
			if (theIVector.at(theIndex) == theIndex) {
				notIndex = false;
			}

			else {
				theIndex = theIVector.at(theIndex);
			}
		}

		otherElementi2 = theIVector.at(theIndex);

		std::pair<double, bool> theRelationI1andI2 = (*theMatrixC)(anElementi1, otherElementi2);

		if (!std::get<1>(theRelationI1andI2)) {
			tempMaxSimilarity = -1.00;
			nbm[anElementi1] = std::pair<int, double> (-1, -1.00);

			for (int i = 0; i < totalElements; ++i) {
				double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
				bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));

				if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector.at(i) == i && canMergeI1WithI) {
					tempMaxSimilarity = tempSimilarity;
					nbm[anElementi1] = std::pair<int, double> (i, tempMaxSimilarity);
				}
			}

			continue;
		}

		//copio elementos al cluster correspondiente
		std::set<Flake> besti1;

		try {
			besti1 = clustering.at(anElementi1);
		}

		catch (const std::out_of_range& oor) {
			throw Exception(__FILE__, __LINE__, oor.what());
		}

		std::set<Flake> besti2;

		try {
			besti2 = clustering.at(otherElementi2);
		}

		catch (const std::out_of_range& oor) {
			throw Exception(__FILE__, __LINE__, oor.what());
		}

		besti1.insert(besti2.begin(), besti2.end());
		clustering.erase(otherElementi2);

		//actualizacion del vector de indices y de la matriz de similitud
		for (int i = 0; i < totalElements; ++i) {
			if (theIVector.at(i) == i && i != anElementi1 && i != otherElementi2) {
				double similarityI1 = std::get<0>((*theMatrixC)(anElementi1, i));

				double similarityI2 = std::get<0>((*theMatrixC)(otherElementi2, i));

				double maxSimilarity = (similarityI1 > similarityI2) ? similarityI1 : similarityI2;
				bool canMergeI1WithI2 = checkBudgetAndCoverageConstraint(clustering.at(anElementi1),
                                                                         clustering.at(theIVector.at(i)),
                                                                         theProblem);

				theMatrixC->insert_element(anElementi1, i, std::pair<double, bool>(maxSimilarity, canMergeI1WithI2));
				theMatrixC->insert_element(i, anElementi1, std::pair<double, bool>(maxSimilarity, canMergeI1WithI2));
			}

			if (theIVector.at(i) == otherElementi2) {
				theIVector[i] = anElementi1;
			}
		}

		//actualizo nbm
		tempMaxSimilarity = -1.00;
		nbm[anElementi1] = std::pair<int, double> (-1, -1.00);

		for (int i = 0; i < totalElements; ++i) {
			double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
			bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));

			if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector.at(i) == i && canMergeI1WithI) {
				tempMaxSimilarity = tempSimilarity;
				nbm[anElementi1] = std::pair<int, double> (i, tempMaxSimilarity);
			}
		}

		++j;
	}

	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (auto aTuple : clustering) {
		SnowFlake aFlake(aTuple.second);
		solution.push_back(aFlake);
	}

	delete theMatrixC;

	return solution;
}

//ESTA ES LA IMPLEMENTACION ORIGINAL n^3
std::vector<SnowFlake> RestrictedHACSolver::produceManySnowflakes1(int numToProduce, ProblemInstance &theProblem)
{
	/*if (this->problem_->numNodes() < numToProduce) {
		//ARROJAR EXCEPCION Too few nodes
	}
	// Put each item in its own cluster
	std::map<int, std::set<int>*> clustering = std::map<int, std::set<int>*>();
	std::set<int> ids = this->problem_->getIds();
	for (std::set<int>::iterator it = ids.begin(); it != ids.end(); ++it) {
		// Make sure all singleton clusters are within budget
		if (this->problem_->getCost(*it) <= this->problem_->getbudget()) {
			std::set<int> temp = std::set<int>();
			temp.insert(*it);
			clustering[*it] = temp;
		}
	}
	// Merge iteratively
	bool merged = true;
	while(merged && clustering.size() > numToProduce) {
		merged = tryMerge(clustering);
	}

	if( merged == false ) {
		//not merged
	}
	SnowFlakeVector* solution = new SnowFlakeVector;
	for (std::map<int, std::set<int>*>::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(it->second, this->problem_);
		solution->push_back(*aFlake);
	}

	return solution;*/
	return std::vector<SnowFlake>();
}

bool RestrictedHACSolver::tryMerge(std::map<int, std::set<int>*>* clustering)
{
	/*
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	double maxCompatibility = -1.00;
	for (std::map<int, std::set<int>*>::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		std::set<int> cluster1 = it->second;
		for (std::map<int, std::set<int>*>::iterator it2 = it; it != clustering.end(); ++it2) {
			if (it == it2) {
				continue;
			}
			std::set<int> cluster2 = it2->second;
			//check if these can be merged
			if (this->checkBudgetAndCoverageConstraint(cluster1, cluster2)) {
				// if they can be merged, measure their compatibility
				double compatibility = this->problem_->maxPairwiseCompatibility(cluster1, cluster2);
				if (compatibility > maxCompatibility) {
					bestC1 = it->first;
					bestC2 = it2->first;
					maxCompatibility = compatibility;
				}
			}
		}
	}

	if (bestC1 >= 0 && bestC2 >= 0) {
		//copy elements from c2 into c1
		std::set<int> bestSetC2 = clustering.at(bestC2);
		clustering.at(bestC1).insert(bestSetC2.begin(), bestSetC2.end());

		//remove c2 from cluster
		clustering.erase(bestC2);
		return true;
	}
	else {
		return false;
	}
	*/
	return false;
}