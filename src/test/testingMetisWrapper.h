/*
 * testingMetisWrapper.h
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#ifndef TESTINGMETISWRAPPER_H_
#define TESTINGMETISWRAPPER_H_

#include "../matrix/matrixConcrete.h"
#include "../cluster/metisWrapper.h"

class TestingMetisWrapper {
private:
	MetisWrapper* metis_;
public:
	TestingMetisWrapper();
	~TestingMetisWrapper();

	void testCluster(const MatrixWrapper& graph, int numClusters);
};

#endif /* TESTINGMETISWRAPPER_H_ */
