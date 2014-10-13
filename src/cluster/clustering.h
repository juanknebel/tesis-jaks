/*
 * clustering.h
 *
 *  Created on: Aug 15, 2013
 *      Author: amit
 */

#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include "../matrix/matrixWrapper.h"

class Clustering {
public:
	Clustering();
	~Clustering();

	static IntVector* cluster(const MatrixWrapper& graph, int numClusters);
	static IntVector* symmetrizeAndCluster(MatrixWrapper& graph, int numClusters);
};

#endif /* CLUSTERING_H_ */
