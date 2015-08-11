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

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes(int numToProduce) {
    MapIntIntSet *clustering = new MapIntIntSet();
    int totalElements = this->problem_->numNodes();
    matrix<int> *theMatrixC = new matrix<int> (totalElements, totalElements);
    BoolVector *theIVector = new BoolVector;
    VectorPrtyQueueTupleIntDouble *theVectorPriorityQueue = new VectorPrtyQueueTupleIntDouble;

    /*
     * Inicializo la matriz de similitudes, vector de decision y vector con la cola de prioridad
     */
    for (int i = 0; i < totalElements; ++i) {
        /*
         * Inicializo el clustering
         */
        IntSet *temp = new IntSet();
        temp->insert(i);
        (*clustering)[i] = temp;

        /*
         * Al principio todas las filas se pueden juntar
         */
        theIVector->push_back(true);
        /*
         * Inicializo el vector de pilas de prioridades
         */
        PriorityQueue *thePriorityQueue = new PriorityQueue();
        for (int j = 0; j < totalElements; ++j) {
            /*
             * En la posicion j del vector se encuentra la pila de prioridad de la fila i ordenada por la similitud
             * entre el elemento i y j. La similitud de un elemento consigo mismo no la guardo
             */
            if (i != j) {
                IntSet *temp2 = new IntSet();
                temp2->insert(j);
                double similarity = sim(temp, temp2);
                int key = thePriorityQueue->push(TupleIntDouble(j, similarity));
                theMatrixC->insert_element(i, j, key);
                delete temp2;
            }
        }
        theVectorPriorityQueue->push_back(thePriorityQueue);
    }

    /*
     * Empizo con la clusterizacion
     */
    for (int k = 0; k < totalElements - 1; ++k) {
        Double maxSimilarity = -1.0;
        int k1Index = -1, k2Index = -1;
        /*
         * Busco la maxima similitud en todas las colas de prioridad
         */
        for (int j = 0; j < totalElements; ++j) {
            if (theIVector->at(j) == true) {
                PriorityQueue* queuep = theVectorPriorityQueue->at(j);
                TupleIntDouble tempTuple = queuep->top();
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
        (*theIVector)[k2Index] = false;
        PriorityQueue *thePriorityQueueAtK1 = theVectorPriorityQueue->at(k1Index);
        delete thePriorityQueueAtK1;
        (*theVectorPriorityQueue)[k1Index] = new PriorityQueue();

        /*
         *  Agrego al cluster correspondiente del k1, los elementos del cluester del k2
         */
        IntSet *theK1Cluster;
        try {
            theK1Cluster = clustering->at(k1Index);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        IntSet *theK2Cluster;
        try {
            theK2Cluster = clustering->at(k2Index);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        theK1Cluster->insert(theK2Cluster->begin(), theK2Cluster->end());
        clustering->erase(k2Index);


        /*
         * Actualizo la matriz y vectores
         */
        for (int i = 0; i < totalElements; ++i) {
            if ((*theIVector)[i] == true && i != k1Index) {
                (*theMatrixC)(i, k2Index);
                theVectorPriorityQueue->at(i)->erase((*theMatrixC)(i, k1Index));
                theVectorPriorityQueue->at(i)->erase((*theMatrixC)(i, k2Index));
                double similarity = sim(theK1Cluster, clustering->at(i));
                TupleIntDouble tupleAtIK1 = TupleIntDouble(k1Index, similarity);
                TupleIntDouble tupleAtK1I = TupleIntDouble(i, similarity);
                int key1 = (*theVectorPriorityQueue)[i]->push(tupleAtIK1);
                int key2= (*theVectorPriorityQueue)[k1Index]->push(tupleAtK1I);
                theMatrixC->insert_element(i, k1Index, key1);
                theMatrixC->insert_element(k1Index, i, key2);

            }
        }
    }

    SnowFlakeVector* solution = new SnowFlakeVector;
    for (MapIntIntSet::iterator it = clustering->begin(); it != clustering->end(); ++it) {
        SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
        solution->push_back(*aFlake);
    }
    //WriterSolution::writeSnowFlakeIds(*solution, "/home/zero/tmp/clusters.txt");
    //WriterSolution::writeInterAndIntraValues(*solution, "/home/zero/tmp/articles/intraintercompleto.txt");

    delete theMatrixC;
    delete theIVector;
    delete theVectorPriorityQueue;
    delete clustering;

    return solution;
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakesSingleCluster(int numToProduce) {
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
        SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
        solution->push_back(*aFlake);
    }

    delete theIVector;
    delete theMatrixC;
    delete nbm;
    delete clustering;

    return solution;
}

double RestrictedHACSolver::sim(IntSet* snowflake1, IntSet* snowflake2) {
    bool check = this->checkBudgetAndCoverageConstraint(*snowflake1, *snowflake2);
    if (check) {
        Double intra = 0.0;
        for (IntSet::iterator it = snowflake1->begin(); it != snowflake1->end(); ++it) {
            for (IntSet::iterator it2 = snowflake1->begin(); it2 != snowflake1->end(); ++it2) {
                if (*it<*it2) {
                    intra += this->problem_->getCompat(*it, *it2);
                }
            }
        }
        for (IntSet::iterator it = snowflake2->begin(); it != snowflake2->end(); ++it) {
            for (IntSet::iterator it2 = snowflake2->begin(); it2 != snowflake2->end(); ++it2) {
                if (*it<*it2) {
                    intra += this->problem_->getCompat(*it, *it2);
                }
            }
        }
        for (IntSet::iterator it = snowflake1->begin(); it != snowflake1->end(); ++it) {
            for (IntSet::iterator it2 = snowflake2->begin(); it2 != snowflake2->end(); ++it2) {
                intra += this->problem_->getCompat(*it, *it2);
            }
        }

        Double gamma = 1.0 - this->interSimilarityWeight_;
        double inter = this->problem_->maxPairwiseCompatibility(*snowflake1, *snowflake2);
        return (gamma * intra) + ((1.0 - gamma) * inter);
    }
    
    return -1.0;
}
