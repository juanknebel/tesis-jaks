/*
 * testingMetisWrapper.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include "testingMetisWrapper.h"
#include <iostream>

TestingMetisWrapper::TestingMetisWrapper()
{
	this->metis_ = new MetisWrapper();
}

TestingMetisWrapper::~TestingMetisWrapper()
{
	delete this->metis_;
}

void TestingMetisWrapper::testCluster(const MatrixWrapper& graph, int numClusters)
{
	std::vector<int>* result = this->metis_->cluster(graph, numClusters);

	for (int node = 0; node < result->size(); ++node) {
		std::cout<<"El nodo: "<<node<<" pertence a la particion: "<<(*result)[node]<<std::endl;
	}

	delete result;
}
