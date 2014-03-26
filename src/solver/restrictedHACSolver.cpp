/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"
#include "../util/Logger.h"

RestrictedHACSolver::~RestrictedHACSolver() {
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes(int numToProduce) {
	if (this->problem_->numNodes() < numToProduce) {
		throw Exception(__FILE__, __LINE__, "IllegalArgumentException Too few nodes");
	}
	// Put each item in its own cluster
    MapIntIntSet *clustering = new MapIntIntSet();
    int totalElements = this->problem_->numNodes();

    matrix<Double> *theMatrixC = new matrix<Double> (totalElements, totalElements);
    IntVector *theIVector = new IntVector;
    TupleIntDoubleVector *nbm = new TupleIntDoubleVector;
    Double tempMaxSimilarity, similarity;
    int tempMaxIndex;
    //Inicializo el cluster, la matriz con las similitudes, vector de indices y nbm
    for (int i = 0; i < totalElements; ++i) {
        //init del clustering
        IntSet *temp = new IntSet();
        temp->insert(i);
        (*clustering)[i] = temp;
        //init de matriz y vectores
        tempMaxSimilarity = -1.00;
        tempMaxIndex = -1;
        for (int j = 0; j < totalElements; ++j) {
            similarity = this->problem_->getCompat(i, j);
            if (similarity > tempMaxSimilarity && i != j) {
                tempMaxIndex = j;
                tempMaxSimilarity = similarity;
            }
            theMatrixC->insert_element(i, j, similarity);
        }
        theIVector->push_back(i);
        TupleIntDouble otherValue (tempMaxIndex, tempMaxSimilarity);
        nbm->push_back(otherValue);
    }

    //Empiezo a intentar clusterizar
    int j = 0;
    while (j < totalElements - 1 && clustering->size() > numToProduce) {
        DEBUG(DBG_DEBUG,"tamanio del cluster " << clustering->size());
        tempMaxSimilarity = -1.00;
        int anElementi1, otherElementi2;
        //Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento
        DEBUG(DBG_DEBUG,"Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento");
        for (int k = 0; k < totalElements; ++k) {
            TupleIntDouble aTupleToCompare = nbm->at(k);
            if (std::get<1>(aTupleToCompare) > tempMaxSimilarity && k == theIVector->at(k)) {
                anElementi1 = k;
                tempMaxSimilarity = std::get<1>(aTupleToCompare);
            }
        }

        //busco recursivamente el segundo elemento
        int theIndex = std::get<0>(nbm->at(anElementi1));
        bool notIndex = true;
        while (notIndex == true) {
            if (theIVector->at(theIndex) == theIndex) {
                notIndex = false;
            }
            else {
                theIndex = theIVector->at(theIndex);
            }
        }
        otherElementi2 = theIVector->at(theIndex);

        //copio elementos al cluster correspondiente
        DEBUG(DBG_DEBUG,"copio elementos al cluster correspondiente");
        DEBUG(DBG_DEBUG,"i1 "<<anElementi1);
        IntSet *besti1 = clustering->at(anElementi1);
        DEBUG(DBG_DEBUG,"i2 "<<otherElementi2);
        IntSet *besti2 = clustering->at(otherElementi2);
        besti1->insert(besti2->begin(), besti2->end());
        clustering->erase(otherElementi2);

        //actualizacion del vector de indices y de la matriz de similitud
        DEBUG(DBG_DEBUG,"actualizacion del vector de indices y de la matriz de similitud");
        for (int i = 0; i < totalElements; ++i) {
            if (theIVector->at(i) == i && i != anElementi1 && i != otherElementi2) {

                Double similarityI1 = (*theMatrixC)(anElementi1, i);
                Double similarityI2 = (*theMatrixC)(otherElementi2, i);
                Double maxSimilarity = (similarityI1 > similarityI2) ? similarityI1 : similarityI2;
                theMatrixC->insert_element(anElementi1, i, maxSimilarity);
                theMatrixC->insert_element(i, anElementi1, maxSimilarity);

            }
            if (theIVector->at(i) == otherElementi2) {
                (*theIVector)[i] = anElementi1;
            }
        }
        //actualizo nbm
        DEBUG(DBG_DEBUG,"actualizo nbm");
        tempMaxSimilarity = -1.00;
        for (int i = 0; i < totalElements; ++i) {
            Double tempSimilarity = (*theMatrixC)(anElementi1, i);
            if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i) {
                tempMaxSimilarity = tempSimilarity;
                (*nbm)[anElementi1] = TupleIntDouble (i, tempMaxSimilarity);
            }
        }
        ++j;
    }

	SnowFlakeVector* solution = new SnowFlakeVector;
    for (MapIntIntSet::iterator it = clustering->begin(); it != clustering->end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
		solution->push_back(*aFlake);
	}

    delete theIVector;
    delete theMatrixC;
    delete nbm;
	delete clustering;

	return solution;
}

void RestrictedHACSolver::singleLinkClustering(MapIntIntSet* clustering) {

}
