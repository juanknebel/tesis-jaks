/*
 * clustering.h
 *
 *  Created on: Aug 15, 2013
 *      Author: amit
 */

#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include <vector>
#include "../matrix/matrixWrapper.h"

class Clustering {
public:
	Clustering();
	~Clustering();

	static std::vector<int>* cluster(const MatrixWrapper& graph, int numClusters);
	static std::vector<int>* symmetrizeAndCluster(MatrixWrapper& graph, int numClusters);
};

#endif /* CLUSTERING_H_ */
