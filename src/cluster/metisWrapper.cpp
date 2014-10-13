/*
 * metisWrapper.cpp
 *
 *  Created on: 21/08/2013
 *      Author: jknebel
 */

#include <cstdlib>
#include <cassert>
#include "metisWrapper.h"
#include "../util/system/stringUtilities.h"
#include "../util/system/systemUtilities.h"
#include "../util/system/Logger.h"

int MetisWrapper::PRECISION_DOUBLE_TO_INTEGER = 1000;
String MetisWrapper::METIS_COMMAND = "gpmetis"; //para la version 5.x de metis
//String MetisWrapper::METIS_COMMAND = "kmetis"; //para la version 4.x o anterior de metis
String MetisWrapper::TEMP_METIS_FILENAME = "metis-input.tmp";

String MetisWrapper::run(int argc, char *argv[]) {
	return runExternalProgram(argc, argv);
}

MetisWrapper::MetisWrapper() {

}

MetisWrapper::~MetisWrapper() {

}

IntVector* MetisWrapper::cluster(const MatrixWrapper& graph, int numClusters) {
	if (graph.getRows() != graph.getCols()) {
		assert(graph.getRows() != graph.getCols());
	}
	int nodes = graph.getRows();
	int edges = graph.countNonZeros();
	FileOutput tempFile(MetisWrapper::TEMP_METIS_FILENAME.c_str());
	tempFile<<nodes<<" "<<(int) (edges / 2)<<" "<<1<<"\n";
	for (int node = 0; node < nodes; ++node) {
		bool firstNeighbor = true;
		for (int neighbor = 0; neighbor < nodes; neighbor++) {
			if (graph.get(node, neighbor) > 0) {
				if (graph.get(neighbor, node) != graph.get(node, neighbor)) {
					assert(graph.get(neighbor, node) != graph.get(node, neighbor));
				}
				if (firstNeighbor) {
					firstNeighbor = false;
				}
				else {
					tempFile<<" ";
				}
				tempFile<<(neighbor + 1)<<" "<<(int) graph.get(node, neighbor);
			}
		}
		tempFile<<"\n";
	}
	tempFile.close();
	String nclusters = convertToString(numClusters);
	char* command [3]= {&MetisWrapper::METIS_COMMAND[0], &MetisWrapper::TEMP_METIS_FILENAME[0], &nclusters[0]};
	String output = MetisWrapper::run(3, command);
	DEBUG(DBG_DEBUG, output);
	FileInput resultFile((MetisWrapper::TEMP_METIS_FILENAME + ".part." + convertToString(numClusters)).c_str());
	/*
	 * if (resultFile no existe)
	 * poner error de que no se genero el archivo de salida
	 *
	 */
	IntVector *result = new IntVector(nodes);
	String line;
	int node = 0;
	while(getline(resultFile, line, '\n')) {
		int cluster = atoi(line.c_str());
		(*result)[node] = cluster;
		++node;
	}
	resultFile.close();
	return result;
}
