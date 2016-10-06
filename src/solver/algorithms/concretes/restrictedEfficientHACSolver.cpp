/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedEfficientHACSolver.h"
#include "../../../problem/factoryFlake.h"
#include <map>

RestrictedEfficientHACSolver::~RestrictedEfficientHACSolver()
{
}

// ESTE ES NUESTRA IMPLEMENTACION
std::vector<SnowFlake> RestrictedEfficientHACSolver::produceManySnowflakes(int numToProduce, ProblemInstance &theProblem)
{
	std::map<int,std::set<Flake>> clustering;
	int totalElements = theProblem.numNodes();
	matrix<int> *theMatrixC = new matrix<int> (totalElements, totalElements);
	std::vector<bool> theIVector;
	VectorPrtyQueueTupleIntDouble theVectorPriorityQueue;

	/*
	 * Inicializo la matriz de similitudes, vector de decision y vector con la cola de prioridad
	 */
	for (int i = 0; i < totalElements; ++i) {
		/*
		 * Inicializo el clustering
		 */
		std::set<Flake> temp = std::set<Flake>();
		temp.insert(FactoryFlake::createNewFlake(i, theProblem));
		clustering[i] = temp;

		/*
		 * Al principio todas las filas se pueden juntar
		 */
		theIVector.push_back(true);
		/*
		 * Inicializo el vector de pilas de prioridades
		 */
		PriorityQueue thePriorityQueue = PriorityQueue();

		for (int j = 0; j < totalElements; ++j) {
			/*
			 * En la posicion j del vector se encuentra la pila de prioridad de la fila i ordenada por la similitud
			 * entre el elemento i y j. La similitud de un elemento consigo mismo no la guardo
			 */
			if (i != j) {
				std::set<Flake> temp2 = std::set<Flake>();
				temp2.insert(FactoryFlake::createNewFlake(j, theProblem));
				double similarity = sim(temp, temp2, theProblem);
				int key = thePriorityQueue.push(std::pair<int, double>(j, similarity));
				theMatrixC->insert_element(i, j, key);
			}
		}

		theVectorPriorityQueue.push_back(thePriorityQueue);
	}

	/*
	 * Empizo con la clusterizacion
	 */
	for (int k = 0; k < totalElements - 1; ++k) {
		double maxSimilarity = -1.0;
		int k1Index = -1, k2Index = -1;

		/*
		 * Busco la maxima similitud en todas las colas de prioridad
		 */
		for (int j = 0; j < totalElements; ++j) {
			if (theIVector.at(j) == true) {
				PriorityQueue queuep = theVectorPriorityQueue.at(j);
				std::pair<int, double> tempTuple = queuep.top();

				if (std::get<1>(tempTuple) > maxSimilarity) {
					maxSimilarity = std::get<1>(tempTuple);
					k1Index = j;
					k2Index = std::get<0>(tempTuple);
				}
			}
		}

		if (k2Index < 0) break;

		/*
		 * Actualizo la posicion del vector k2 porque ya lo uni a un cluster
		 * Y genero una nueva pila en la posicion k1 porque ahora tengo un nuevo cluster
		 */
		theIVector[k2Index] = false;
		PriorityQueue thePriorityQueueAtK1 = theVectorPriorityQueue.at(k1Index);
		theVectorPriorityQueue[k1Index] = PriorityQueue();

		/*
		 *  Agrego al cluster correspondiente del k1, los elementos del cluester del k2
		 */
		std::set<Flake> theK1Cluster;

		try {
			theK1Cluster = clustering.at(k1Index);
		}

		catch (const std::out_of_range& oor) {
			throw Exception(__FILE__, __LINE__, oor.what());
		}

		std::set<Flake> theK2Cluster;

		try {
			theK2Cluster = clustering.at(k2Index);
		}

		catch (const std::out_of_range& oor) {
			throw Exception(__FILE__, __LINE__, oor.what());
		}

		theK1Cluster.insert(theK2Cluster.begin(), theK2Cluster.end());
		clustering.erase(k2Index);


		/*
		 * Actualizo la matriz y vectores
		 */
		for (int i = 0; i < totalElements; ++i) {
			if (theIVector[i] == true && i != k1Index) {
				(*theMatrixC)(i, k2Index);
				theVectorPriorityQueue.at(i).erase((*theMatrixC)(i, k1Index));
				theVectorPriorityQueue.at(i).erase((*theMatrixC)(i, k2Index));
				double similarity = sim(theK1Cluster, clustering.at(i), theProblem);
				std::pair<int, double> tupleAtIK1 = std::pair<int, double>(k1Index, similarity);
				std::pair<int, double> tupleAtK1I = std::pair<int, double>(i, similarity);
				int key1 = theVectorPriorityQueue[i].push(tupleAtIK1);
				int key2= theVectorPriorityQueue[k1Index].push(tupleAtK1I);
				theMatrixC->insert_element(i, k1Index, key1);
				theMatrixC->insert_element(k1Index, i, key2);

			}
		}
	}

	std::vector<SnowFlake> solution = std::vector<SnowFlake>();

	for (auto it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake aFlake(it->second);
		solution.push_back(aFlake);
	}

	delete theMatrixC;
	return solution;
}

double RestrictedEfficientHACSolver::sim(std::set<Flake> &snowflake1, std::set<Flake> &snowflake2,
										 ProblemInstance &theProblem)
{
	bool check = this->checkBudgetAndCoverageConstraint(snowflake1, snowflake2, theProblem);

	if (check) {
		double intra = 0.0;

		for (auto aFlake : snowflake1) {
			for (auto otherFlake : snowflake1) {
				if (aFlake.getId() < otherFlake.getId()) {
					intra += Flake::getCompat(aFlake, otherFlake, theProblem);
				}
			}
		}

		for (auto aFlake : snowflake2) {
			for (auto otherFlake : snowflake2) {
				if (aFlake.getId() < otherFlake.getId()) {
					intra += Flake::getCompat(aFlake, otherFlake, theProblem);
				}
			}
		}

		for (auto aFlake : snowflake1) {
			for (auto otherFlake : snowflake2) {
				intra += Flake::getCompat(aFlake, otherFlake, theProblem);
			}
		}

		double gamma = 1.0 - this->interSimilarityWeight_;
		double inter = SnowFlake::maxPairwiseCompatibility(snowflake1, snowflake2, theProblem);
		int multiplier = ((snowflake1.size() + snowflake2.size()) * ((snowflake1.size() + snowflake2.size()) - 1)) / 2;
		return (gamma * intra) + multiplier * ((1.0 - gamma) * inter);
	}

	return -1.0;
}
