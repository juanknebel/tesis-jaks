//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

/*
* Forma de uso:
* tesis-jaks -n <configuraciones> [-l]	(para usar con las configuraciones enviadas)
* tesis-jaks -t [-l]					(para usar con los test internos)
* tesis-jaks -s [-l]					(para calcular la similaridad)
* tesis-jaks -h						(para ver el modo de uso)
*
* Use mode:
* tesis-jaks -n <configurations> [-l]		(to use a configuration mode)
* tesis-jaks -t [-l]					(for use with the internal test)
* tesis-jaks -s [-l]					(to calculate the similarity)
* tesis-jaks -h						(to see the use mode)
*/

#include <iostream>
#include "executeSolver.h"
#include "test/testSuites.h"
#include "util/algorithm/vectornorm.h"

const std::string useMode = "tesis-jaks -n <configurations> [-l]\t(to use a configuration file)\ntesis-jaks -t [-l]\t\t\t\t(for use with the internal test)\ntesis-jaks -s [-l]\t\t\t\t(to calculate the similarity)\ntesis-jaks -h\t\t\t\t\t(to see this help)\nThe Argument -l initialize the logger.\nArguments in [] are optional.";
std::string errorMsg = "Bad Arguments. Use -h to see how to use.";

void usingTestHardcode(int argc, char **argv)
{
	//testOverLoadFunction();
	testDB();
	//testMatrix();
	//testProblemInstanceFromFiles("../files/");
	//testMetisWrapper();
	//testClustering();
	//testClusterAndPickSolver("../files/");
	//testConfiguration(argc, argv);
}

std::vector<float> generateVector(char *theVector, int dimension)
{
	std::vector<float> vectorProfile = std::vector<float>();
	std::string separator = "-";
	std::vector<std::string> vectorString;

	stringToVectorSplit(theVector,separator,vectorString);

	for (std::vector<string>::const_iterator i = vectorString.begin(); i != vectorString.end(); ++i) {
		vectorProfile.push_back(convertToDouble(*i));
	}

	return vectorProfile;
}

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		std::cerr<<errorMsg<<std::endl;
	}

	else {
		if (argv[1][0] != '-') {
			std::cerr<<errorMsg<<std::endl;
		}

		else {
			char option = argv[1][1];

			switch(option) {
			case 'n': {
				std::cout<<"Using the configuration file ..."<<std::endl;
                executeNew(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]);
				break;
			}

			case 't': {
				std::cout<<"Using internal tests ..."<<std::endl;
				usingTestHardcode(argc, argv);
				break;
			}

			case 's': {
				std::cout<<"Calculating the similarity ..."<<std::endl;
				insertSimilarity();
				break;
			}

			case 'p': {
				std::cout<<"Calculating the similarity of the specific profile ..."<<std::endl;
				std::vector<float> specificProfile = generateVector(argv[2], convertToInt(argv[3]));

				if (!specificProfile.empty()) {
					insertSimilarity(specificProfile);
				}

				else {
					std::cerr<<"Error el vector de entrada"<<std::endl;
				}

				break;
			}

			case 'h': {
				std::cout<<"Use mode:"<<std::endl<<useMode<<std::endl;
				break;
			}

			default: {
				std::cerr<<errorMsg<<std::endl;
				break;
			}
			}
		}
	}

	exit(EXIT_SUCCESS);
}
