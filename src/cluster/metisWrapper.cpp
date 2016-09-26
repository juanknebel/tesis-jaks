/*
 * metisWrapper.cpp
 *
 *  Created on: 21/08/2013
 *      Author: jknebel
 */


#include "metisWrapper.h"
#include "../util/system/stringUtilities.h"
#include "../util/system/systemUtilities.h"

int MetisWrapper::PRECISION_DOUBLE_TO_INTEGER = 1000;
std::string MetisWrapper::METIS_COMMAND = "gpmetis"; //para la version 5.x de metis
//std::string MetisWrapper::METIS_COMMAND = "kmetis"; //para la version 4.x o anterior de metis
std::string MetisWrapper::TEMP_METIS_FILENAME = "metis-input.tmp";

std::string MetisWrapper::run(int argc, char *argv[])
{
	return runExternalProgram(argc, argv);
}

MetisWrapper::MetisWrapper()
{

}

MetisWrapper::~MetisWrapper()
{

}

std::vector<int>* MetisWrapper::cluster(const MatrixWrapper& graph, int numClusters)
{
	if (graph.getRows() != graph.getCols()) {
		assert(graph.getRows() != graph.getCols());
	}

	int nodes = graph.getRows();
	int edges = graph.countNonZeros();
	std::ofstream tempFile(MetisWrapper::TEMP_METIS_FILENAME.c_str());
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
	std::string nclusters = convertToString(numClusters);
	char* command [3]= {&MetisWrapper::METIS_COMMAND[0], &MetisWrapper::TEMP_METIS_FILENAME[0], &nclusters[0]};
	std::string output = MetisWrapper::run(3, command);
	std::ifstream resultFile((MetisWrapper::TEMP_METIS_FILENAME + ".part." + convertToString(numClusters)).c_str());
	/*
	 * if (resultFile no existe)
	 * poner error de que no se genero el archivo de salida
	 *
	 */
	std::vector<int> *result = new std::vector<int>(nodes);
	std::string line;
	int node = 0;

	while(getline(resultFile, line, '\n')) {
		int cluster = atoi(line.c_str());
		(*result)[node] = cluster;
		++node;
	}

	resultFile.close();
	return result;
}
