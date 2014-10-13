/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"
#include "../util/system/Logger.h"

RestrictedHACSolver::~RestrictedHACSolver() {
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakesOLD(int numToProduce) {
	if (this->problem_->numNodes() < numToProduce) {
		throw Exception(__FILE__, __LINE__, "IllegalArgumentException Too few nodes");
	}
	// Put each item in its own cluster
    MapIntIntSet *clustering = new MapIntIntSet();
    int totalElements = this->problem_->numNodes();

    matrix<TupleDoubleBool> *theMatrixC = new matrix<TupleDoubleBool> (totalElements, totalElements);
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

            IntSet aSetWithElementI = IntSet();
            aSetWithElementI.insert(i);
            IntSet aSetWithElementJ = IntSet();
            aSetWithElementJ.insert(j);
            bool canMergeIandJ = this->checkBudgetAndCoverageConstraint(aSetWithElementI, aSetWithElementJ);

            if (similarity > tempMaxSimilarity && canMergeIandJ) {
                tempMaxIndex = j;
                tempMaxSimilarity = similarity;
            }

            theMatrixC->insert_element(i, j, TupleDoubleBool(similarity, canMergeIandJ));
        }
        theIVector->push_back(i);
        TupleIntDouble theMaxValue (tempMaxIndex, tempMaxSimilarity);
        nbm->push_back(theMaxValue);
    }

    //Empiezo a intentar clusterizar
    int j = 0;
    while (j < totalElements - 1 && clustering->size() > numToProduce) {
        //DEBUG(DBG_DEBUG,"tamanio del cluster " << clustering->size());
        tempMaxSimilarity = -1.00;
        int anElementi1, otherElementi2;
        //Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento
        //DEBUG(DBG_DEBUG,"Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento");
        for (int k = 0; k < totalElements; ++k) {
            TupleIntDouble aTupleToCompare = nbm->at(k);
            if (std::get<1>(aTupleToCompare) > tempMaxSimilarity && k == theIVector->at(k)) {
                anElementi1 = k;
                tempMaxSimilarity = std::get<1>(aTupleToCompare);
            }
        }

        if (tempMaxSimilarity == -1.00) {
            break;
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

        TupleDoubleBool theRelationI1andI2 = (*theMatrixC)(anElementi1, otherElementi2);
        if (!std::get<1>(theRelationI1andI2)) {
            tempMaxSimilarity = -1.00;
            (*nbm)[anElementi1] = TupleIntDouble (-1, -1.00);
            for (int i = 0; i < totalElements; ++i) {
                Double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
                bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
                if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
                    tempMaxSimilarity = tempSimilarity;
                    (*nbm)[anElementi1] = TupleIntDouble (i, tempMaxSimilarity);
                }
            }
            continue;
        }

        //copio elementos al cluster correspondiente
        //DEBUG(DBG_DEBUG,"copio elementos al cluster correspondiente");
        //DEBUG(DBG_DEBUG,"i1 "<<anElementi1);
        IntSet *besti1;
        try {
            besti1 = clustering->at(anElementi1);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        //DEBUG(DBG_DEBUG,"i2 "<<otherElementi2);
        IntSet *besti2;
        try {
            besti2 = clustering->at(otherElementi2);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }

        besti1->insert(besti2->begin(), besti2->end());
        clustering->erase(otherElementi2);

        //actualizacion del vector de indices y de la matriz de similitud
        //DEBUG(DBG_DEBUG,"actualizacion del vector de indices y de la matriz de similitud");
        for (int i = 0; i < totalElements; ++i) {
            if (theIVector->at(i) == i && i != anElementi1 && i != otherElementi2) {
                Double similarityI1 = std::get<0>((*theMatrixC)(anElementi1, i));
                bool canMergeI1 = std::get<1>((*theMatrixC)(anElementi1, i));

                Double similarityI2 = std::get<0>((*theMatrixC)(otherElementi2, i));
                bool canMergeI2 = std::get<1>((*theMatrixC)(otherElementi2, i));

                Double maxSimilarity = (similarityI1 > similarityI2) ? similarityI1 : similarityI2;
                bool canMergeI1WithI2 = checkBudgetAndCoverageConstraint(*(clustering->at(anElementi1)), *(clustering->at(theIVector->at(i))));

                theMatrixC->insert_element(anElementi1, i, TupleDoubleBool(maxSimilarity, canMergeI1WithI2));
                theMatrixC->insert_element(i, anElementi1, TupleDoubleBool(maxSimilarity, canMergeI1WithI2));
            }
            if (theIVector->at(i) == otherElementi2) {
                (*theIVector)[i] = anElementi1;
            }
        }
        //actualizo nbm
        //DEBUG(DBG_DEBUG,"actualizo nbm");
        tempMaxSimilarity = -1.00;
        (*nbm)[anElementi1] = TupleIntDouble (-1, -1.00);
        for (int i = 0; i < totalElements; ++i) {
            Double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
            bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
            if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
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

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes(int numToProduce) {
    if (this->problem_->numNodes() < numToProduce) {
        throw Exception(__FILE__, __LINE__, "IllegalArgumentException Too few nodes");
    }
    // Put each item in its own cluster
    MapIntIntSet *clustering = new MapIntIntSet();
    int totalElements = this->problem_->numNodes();

    matrix<TupleDoubleBool> *theMatrixC = new matrix<TupleDoubleBool> (totalElements, totalElements);
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
            similarity = this->problem_->getCompatWithSpecificProfile(i, j);//ESTA LINEA HAY QUE CAMBIAR

            IntSet aSetWithElementI = IntSet();
            aSetWithElementI.insert(i);
            IntSet aSetWithElementJ = IntSet();
            aSetWithElementJ.insert(j);
            bool canMergeIandJ = this->checkBudgetAndCoverageConstraint(aSetWithElementI, aSetWithElementJ);

            if (similarity > tempMaxSimilarity && canMergeIandJ) {
                tempMaxIndex = j;
                tempMaxSimilarity = similarity;
            }

            theMatrixC->insert_element(i, j, TupleDoubleBool(similarity, canMergeIandJ));
        }
        theIVector->push_back(i);
        TupleIntDouble theMaxValue (tempMaxIndex, tempMaxSimilarity);
        nbm->push_back(theMaxValue);
    }

    //Empiezo a intentar clusterizar
    int j = 0;
    while (j < totalElements - 1 && clustering->size() > numToProduce) {
        //DEBUG(DBG_DEBUG,"tamanio del cluster " << clustering->size());
        tempMaxSimilarity = -1.00;
        int anElementi1, otherElementi2;
        //Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento
        //DEBUG(DBG_DEBUG,"Busco en el nbm el elemento que contenga la mayor similitud para algun otro elemento");
        for (int k = 0; k < totalElements; ++k) {
            TupleIntDouble aTupleToCompare = nbm->at(k);
            if (std::get<1>(aTupleToCompare) > tempMaxSimilarity && k == theIVector->at(k)) {
                anElementi1 = k;
                tempMaxSimilarity = std::get<1>(aTupleToCompare);
            }
        }

        if (tempMaxSimilarity == -1.00) {
            break;
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

        TupleDoubleBool theRelationI1andI2 = (*theMatrixC)(anElementi1, otherElementi2);
        if (!std::get<1>(theRelationI1andI2)) {
            tempMaxSimilarity = -1.00;
            (*nbm)[anElementi1] = TupleIntDouble (-1, -1.00);
            for (int i = 0; i < totalElements; ++i) {
                Double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
                bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
                if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
                    tempMaxSimilarity = tempSimilarity;
                    (*nbm)[anElementi1] = TupleIntDouble (i, tempMaxSimilarity);
                }
            }
            continue;
        }

        //copio elementos al cluster correspondiente
        //DEBUG(DBG_DEBUG,"copio elementos al cluster correspondiente");
        //DEBUG(DBG_DEBUG,"i1 "<<anElementi1);
        IntSet *besti1;
        try {
            besti1 = clustering->at(anElementi1);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        //DEBUG(DBG_DEBUG,"i2 "<<otherElementi2);
        IntSet *besti2;
        try {
            besti2 = clustering->at(otherElementi2);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }

        besti1->insert(besti2->begin(), besti2->end());
        clustering->erase(otherElementi2);

        //actualizacion del vector de indices y de la matriz de similitud
        //DEBUG(DBG_DEBUG,"actualizacion del vector de indices y de la matriz de similitud");
        for (int i = 0; i < totalElements; ++i) {
            if (theIVector->at(i) == i && i != anElementi1 && i != otherElementi2) {
                Double similarityI1 = std::get<0>((*theMatrixC)(anElementi1, i));
                bool canMergeI1 = std::get<1>((*theMatrixC)(anElementi1, i));

                Double similarityI2 = std::get<0>((*theMatrixC)(otherElementi2, i));
                bool canMergeI2 = std::get<1>((*theMatrixC)(otherElementi2, i));

                Double maxSimilarity = (similarityI1 > similarityI2) ? similarityI1 : similarityI2;
                bool canMergeI1WithI2 = checkBudgetAndCoverageConstraint(*(clustering->at(anElementi1)), *(clustering->at(theIVector->at(i))));

                theMatrixC->insert_element(anElementi1, i, TupleDoubleBool(maxSimilarity, canMergeI1WithI2));
                theMatrixC->insert_element(i, anElementi1, TupleDoubleBool(maxSimilarity, canMergeI1WithI2));
            }
            if (theIVector->at(i) == otherElementi2) {
                (*theIVector)[i] = anElementi1;
            }
        }
        //actualizo nbm
        //DEBUG(DBG_DEBUG,"actualizo nbm");
        tempMaxSimilarity = -1.00;
        (*nbm)[anElementi1] = TupleIntDouble (-1, -1.00);
        for (int i = 0; i < totalElements; ++i) {
            Double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
            bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
            if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
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
