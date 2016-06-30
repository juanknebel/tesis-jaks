/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"
#include "../util/writer/writerSolution.h"

RestrictedHACSolver::~RestrictedHACSolver() {
}

//ESTA ES LA IMPLEMENTACION VIEJA
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
            if(i == j){
                continue;
            }
            //similarity = this->problem_->getCompatWithSpecificProfile(i, j);//ESTA LINEA HAY QUE CAMBIAR
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

                Double similarityI2 = std::get<0>((*theMatrixC)(otherElementi2, i));

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
        SnowFlake aFlake(*it->second, this->problem_);
        solution->push_back(aFlake);
    }

    delete theIVector;
    delete theMatrixC;
    delete nbm;
    delete clustering;

    return solution;
}

//ESTA ES LA IMPLEMENTACION ORIGINAL n^3
SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes1(int numToProduce) {
	/*if (this->problem_->numNodes() < numToProduce) {
		//ARROJAR EXCEPCION Too few nodes
	}
	// Put each item in its own cluster
	MapIntIntSet clustering = MapIntIntSet();
	IntSet ids = this->problem_->getIds();
	for (IntSet::iterator it = ids.begin(); it != ids.end(); ++it) {
		// Make sure all singleton clusters are within budget
		if (this->problem_->getCost(*it) <= this->problem_->getbudget()) {
			IntSet temp = IntSet();
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
	for (MapIntIntSet::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		SnowFlake *aFlake = new SnowFlake(it->second, this->problem_);
		solution->push_back(*aFlake);
	}

	return solution;*/
}

bool RestrictedHACSolver::tryMerge(MapIntIntSet* clustering) {
    /*
	// Compute all distances
	int bestC1 = -1;
	int bestC2 = -1;
	Double maxCompatibility = -1.00;
	for (MapIntIntSet::iterator it = clustering.begin(); it != clustering.end(); ++it) {
		IntSet cluster1 = it->second;
		for (MapIntIntSet::iterator it2 = it; it != clustering.end(); ++it2) {
			if (it == it2) {
				continue;
			}
			IntSet cluster2 = it2->second;
			//check if these can be merged
			if (this->checkBudgetAndCoverageConstraint(cluster1, cluster2)) {
				// if they can be merged, measure their compatibility
				Double compatibility = this->problem_->maxPairwiseCompatibility(cluster1, cluster2);
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
		IntSet bestSetC2 = clustering.at(bestC2);
		clustering.at(bestC1).insert(bestSetC2.begin(), bestSetC2.end());

		//remove c2 from cluster
		clustering.erase(bestC2);
		return true;
	}
	else {
		return false;
	}
    */
}