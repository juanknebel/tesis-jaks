/*
 * metisWrapper.h
 *
 *  Created on: 21/08/2013
 *      Author: jknebel
 */

#ifndef METISWRAPPER_H_
#define METISWRAPPER_H_

#include "../matrix/matrixConcrete.h"

class MetisWrapper {
private:
	static int PRECISION_DOUBLE_TO_INTEGER;
    static std::string TEMP_METIS_FILENAME;
    static std::string METIS_COMMAND;
    static std::string run(int argc, char *command[]);

public:
	MetisWrapper();
	~MetisWrapper();
	std::vector<int>* cluster(const MatrixWrapper& graph, int numClusters);
};


#endif /* METISWRAPPER_H_ */
