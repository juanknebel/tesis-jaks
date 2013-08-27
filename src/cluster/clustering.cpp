/*
 * clustering.cpp
 *
 *  Created on: Aug 15, 2013
 *      Author: amit
 */

#include "clustering.h"
#include "metisWrapper.h"

Clustering::Clustering() {
}

Clustering::~Clustering() {
}

IntVector* Clustering::cluster(const MatrixWrapper& graph, int numClusters) {
	MetisWrapper metisWrapper;
	return (metisWrapper.cluster(graph, numClusters));
}

IntVector* Clustering::symmetrizeAndCluster(MatrixWrapper& graph, int numClusters) {
	MetisWrapper metisWrapper;
	graph.ensureSymmetric();
	return (metisWrapper.cluster(graph, numClusters));
}
