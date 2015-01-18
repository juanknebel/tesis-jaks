/*
 * restrictedHACSolver.cpp
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#include "restrictedHACSolver.h"
#include "../util/system/Logger.h"
#include "../util/writer/writerSolution.h"

RestrictedHACSolver::~RestrictedHACSolver() {
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakesSingleCluster(int numToProduce) {
    std::map<int, std::set<int>*> *clustering = new std::map<int, std::set<int>*>();
    int totalElements = this->problem_->numNodes();
    matrix<int> *theMatrixC = new matrix<int> (totalElements, totalElements);
    std::vector<bool> *theIVector = new std::vector<bool>;
    VectorPrtyQueueTupleIntDouble *theVectorPriorityQueue = new VectorPrtyQueueTupleIntDouble;

    /*
     * Inicializo la matriz de similitudes, vector de decision y vector con la cola de prioridad
     */
    for (int i = 0; i < totalElements; ++i) {
        /*
         * Inicializo el clustering
         */
        std::set<int> *temp = new std::set<int>();
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
                std::set<int> *temp2 = new std::set<int>();
                temp2->insert(j);
                double similarity = sim(temp, temp2);
                int key = thePriorityQueue->push(std::tuple<int, double>(j, similarity));
                theMatrixC->insert_element(i, j, key);
                delete temp2;
            }
        }
        theVectorPriorityQueue->push_back(thePriorityQueue);
    }

    /*
     * Empizo con la clusterizacion
     */
    DEBUG(DBG_DEBUG, "Incio bucle clusterizacion: " << totalElements);
    for (int k = 0; k < totalElements - 1; ++k) {
        DEBUG(DBG_DEBUG,"iteracion k: " << k);
        double maxSimilarity = -1.0;
        int k1Index = -1, k2Index = -1;
        /*
         * Busco la maxima similitud en todas las colas de prioridad
         */
        DEBUG(DBG_DEBUG,"inicio bucle buscar maxima: " << totalElements);
        for (int j = 0; j < totalElements; ++j) {
            if (theIVector->at(j) == true) {
                PriorityQueue* queuep = theVectorPriorityQueue->at(j);
                std::tuple<int, double> tempTuple = queuep->top();
                if (std::get<1>(tempTuple) > maxSimilarity) {
                    maxSimilarity = std::get<1>(tempTuple);
                    k1Index = j;
                    k2Index = std::get<0>(tempTuple);
                }
            }
        }
        DEBUG(DBG_DEBUG,"fin bucle buscar maxima");
        if (k2Index < 0) break;
        /*
         * Actualizo la posicion del vector k2 porque ya lo uni a un cluster
         * Y genero una nueva pila en la posicion k1 porque ahora tengo un nuevo cluster
         */
        DEBUG(DBG_DEBUG,"Actualizo la posicion del vector");
        (*theIVector)[k2Index] = false;
        PriorityQueue *thePriorityQueueAtK1 = theVectorPriorityQueue->at(k1Index);
        delete thePriorityQueueAtK1;
        (*theVectorPriorityQueue)[k1Index] = new PriorityQueue();

        /*
         *  Agrego al cluster correspondiente del k1, los elementos del cluester del k2
         */
        DEBUG(DBG_DEBUG,"Agrego al cluster");
        std::set<int> *theK1Cluster;
        try {
            theK1Cluster = clustering->at(k1Index);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        std::set<int> *theK2Cluster;
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
        DEBUG(DBG_DEBUG,"Actualizo la matriz y vectores");
        DEBUG(DBG_DEBUG,"inicio bucle actualizacion: " << totalElements);
        for (int i = 0; i < totalElements; ++i) {
            if ((*theIVector)[i] == true && i != k1Index) {
                ;
                (*theMatrixC)(i, k2Index);
                theVectorPriorityQueue->at(i)->erase((*theMatrixC)(i, k1Index));
                theVectorPriorityQueue->at(i)->erase((*theMatrixC)(i, k2Index));
                double similarity = sim(theK1Cluster, clustering->at(i));
                std::tuple<int, double> tupleAtIK1 = std::tuple<int, double>(k1Index, similarity);
                std::tuple<int, double> tupleAtK1I = std::tuple<int, double>(i, similarity);
                int key1 = (*theVectorPriorityQueue)[i]->push(tupleAtIK1);
                int key2= (*theVectorPriorityQueue)[k1Index]->push(tupleAtK1I);
                theMatrixC->insert_element(i, k1Index, key1);
                theMatrixC->insert_element(k1Index, i, key2);

            }
        }
        DEBUG(DBG_DEBUG,"fin bucle actualizacion");
    }

    SnowFlakeVector* solution = new SnowFlakeVector;
    DEBUG(DBG_DEBUG,"inicio bucle crear solucion");
    for (std::map<int, std::set<int>*>::iterator it = clustering->begin(); it != clustering->end(); ++it) {
        SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
        solution->push_back(*aFlake);
    }
    //WriterSolution::writeSnowFlakeIds(*solution, "/home/zero/tmp/clusters.txt");
    //WriterSolution::writeInterAndIntraValues(*solution, "/home/zero/tmp/articles/intraintercompleto.txt");
    DEBUG(DBG_DEBUG,"fin bucle crear solucion");

    DEBUG(DBG_DEBUG,"eliminar objetos");
    delete theMatrixC;
    delete theIVector;
    delete theVectorPriorityQueue;
    delete clustering;

    return solution;
}

SnowFlakeVector* RestrictedHACSolver::produceManySnowflakes(int numToProduce) {
    if (this->problem_->numNodes() < numToProduce) {
        throw Exception(__FILE__, __LINE__, "IllegalArgumentException Too few nodes");
    }
    // Put each item in its own cluster
    std::map<int, std::set<int>*> *clustering = new std::map<int, std::set<int>*>();
    int totalElements = this->problem_->numNodes();

    matrix<std::tuple<double, bool>> *theMatrixC = new matrix<std::tuple<double, bool>> (totalElements, totalElements);
    std::vector<int> *theIVector = new std::vector<int>;
    std::vector<std::tuple<int, double>> *nbm = new std::vector<std::tuple<int, double>>;
    double tempMaxSimilarity, similarity;
    int tempMaxIndex;
    //Inicializo el cluster, la matriz con las similitudes, vector de indices y nbm
    for (int i = 0; i < totalElements; ++i) {
        //init del clustering
        std::set<int> *temp = new std::set<int>();
        temp->insert(i);
        (*clustering)[i] = temp;
        //init de matriz y vectores
        tempMaxSimilarity = -1.00;
        tempMaxIndex = -1;
        for (int j = 0; j < totalElements; ++j) {
            //similarity = this->problem_->getCompatWithSpecificProfile(i, j);//ESTA LINEA HAY QUE CAMBIAR
            similarity = this->problem_->getCompat(i, j);
            std::set<int> aSetWithElementI = std::set<int>();
            aSetWithElementI.insert(i);
            std::set<int> aSetWithElementJ = std::set<int>();
            aSetWithElementJ.insert(j);
            bool canMergeIandJ = this->checkBudgetAndCoverageConstraint(aSetWithElementI, aSetWithElementJ);

            if (similarity > tempMaxSimilarity && canMergeIandJ) {
                tempMaxIndex = j;
                tempMaxSimilarity = similarity;
            }

            theMatrixC->insert_element(i, j, std::tuple<double, bool>(similarity, canMergeIandJ));
        }
        theIVector->push_back(i);
        std::tuple<int, double> theMaxValue (tempMaxIndex, tempMaxSimilarity);
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
            std::tuple<int, double> aTupleToCompare = nbm->at(k);
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

        std::tuple<double, bool> theRelationI1andI2 = (*theMatrixC)(anElementi1, otherElementi2);
        if (!std::get<1>(theRelationI1andI2)) {
            tempMaxSimilarity = -1.00;
            (*nbm)[anElementi1] = std::tuple<int, double> (-1, -1.00);
            for (int i = 0; i < totalElements; ++i) {
                double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
                bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
                if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
                    tempMaxSimilarity = tempSimilarity;
                    (*nbm)[anElementi1] = std::tuple<int, double> (i, tempMaxSimilarity);
                }
            }
            continue;
        }

        //copio elementos al cluster correspondiente
        //DEBUG(DBG_DEBUG,"copio elementos al cluster correspondiente");
        //DEBUG(DBG_DEBUG,"i1 "<<anElementi1);
        std::set<int> *besti1;
        try {
            besti1 = clustering->at(anElementi1);
        }
        catch (const std::out_of_range& oor) {
            throw Exception(__FILE__, __LINE__, oor.what());
        }
        //DEBUG(DBG_DEBUG,"i2 "<<otherElementi2);
        std::set<int> *besti2;
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
                double similarityI1 = std::get<0>((*theMatrixC)(anElementi1, i));

                double similarityI2 = std::get<0>((*theMatrixC)(otherElementi2, i));

                double maxSimilarity = (similarityI1 > similarityI2) ? similarityI1 : similarityI2;
                bool canMergeI1WithI2 = checkBudgetAndCoverageConstraint(*(clustering->at(anElementi1)), *(clustering->at(theIVector->at(i))));

                theMatrixC->insert_element(anElementi1, i, std::tuple<double, bool>(maxSimilarity, canMergeI1WithI2));
                theMatrixC->insert_element(i, anElementi1, std::tuple<double, bool>(maxSimilarity, canMergeI1WithI2));
            }
            if (theIVector->at(i) == otherElementi2) {
                (*theIVector)[i] = anElementi1;
            }
        }
        //actualizo nbm
        //DEBUG(DBG_DEBUG,"actualizo nbm");
        tempMaxSimilarity = -1.00;
        (*nbm)[anElementi1] = std::tuple<int, double> (-1, -1.00);
        for (int i = 0; i < totalElements; ++i) {
            double tempSimilarity = std::get<0>((*theMatrixC)(anElementi1, i));
            bool canMergeI1WithI = std::get<1>((*theMatrixC)(anElementi1, i));
            if (tempSimilarity > tempMaxSimilarity && i != anElementi1 && theIVector->at(i) == i && canMergeI1WithI) {
                tempMaxSimilarity = tempSimilarity;
                (*nbm)[anElementi1] = std::tuple<int, double> (i, tempMaxSimilarity);
            }
        }
        ++j;
    }

    SnowFlakeVector* solution = new SnowFlakeVector;
    for (std::map<int, std::set<int>*>::iterator it = clustering->begin(); it != clustering->end(); ++it) {
        SnowFlake *aFlake = new SnowFlake(*it->second, this->problem_);
        solution->push_back(*aFlake);
    }

    delete theIVector;
    delete theMatrixC;
    delete nbm;
    delete clustering;

    return solution;
}

double RestrictedHACSolver::sim(std::set<int>* snowflake1, std::set<int>* snowflake2) {
    bool check = this->checkBudgetAndCoverageConstraint(*snowflake1, *snowflake2);
    if (check) {
        double intra = 0.0;
        for (std::set<int>::iterator it = snowflake1->begin(); it != snowflake1->end(); ++it) {
            for (std::set<int>::iterator it2 = snowflake1->begin(); it2 != snowflake1->end(); ++it2) {
                if (*it<*it2) {
                    intra += this->problem_->getCompat(*it, *it2);
                }
            }
        }
        for (std::set<int>::iterator it = snowflake2->begin(); it != snowflake2->end(); ++it) {
            for (std::set<int>::iterator it2 = snowflake2->begin(); it2 != snowflake2->end(); ++it2) {
                if (*it<*it2) {
                    intra += this->problem_->getCompat(*it, *it2);
                }
            }
        }
        for (std::set<int>::iterator it = snowflake1->begin(); it != snowflake1->end(); ++it) {
            for (std::set<int>::iterator it2 = snowflake2->begin(); it2 != snowflake2->end(); ++it2) {
                intra += this->problem_->getCompat(*it, *it2);
            }
        }

        double gamma = 1.0 - this->interSimilarityWeight_;
        double inter = this->problem_->maxPairwiseCompatibility(*snowflake1, *snowflake2);
        return (gamma * intra) + ((1.0 - gamma) * inter);
    }
    
    return -1.0;
}
