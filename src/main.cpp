//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "executeSolver.h"
#include "test/testSuites.h"
#include <boost/program_options.hpp>
#include "util/algorithm/vectornorm.h"

std::string version = "0.9-beta";

namespace po = boost::program_options;

void usingTestHardcode()
{
	//testOverLoadFunction();
	testDB();
	//testMatrix();
	//testProblemInstanceFromFiles("../files/");
	//testMetisWrapper();
	//testClustering();
	//testClusterAndPickSolver("../files/");
	//testConfiguration();
}

/*
 *
 */

bool processCommandLine(int argc, char ** argv, int& option, std::string& element, std::string& algorithm, std::string& strategy,
                        double& budget, double& gamma, int& numFlakes, int& maxIter, int& toProduce, bool& writeToFile, bool& printToScreen)
{
    std::string errorMsg = "Bad Arguments. Use -h to see how to use.";

    try {
        po::options_description desc("tesis-jaks use");
        desc.add_options()
                ("help,h", "Muestra el mensaje de ayuda")
                ("version,v", "Muestra el número de version")
                ("option,o", po::value<int>(&option)->required(), "Opciones de ejecución")
                ("element,e", po::value<std::string>(&element)->required(), "Elemento: AUTHOR, ARTICLE, AFFILIATION, FILE")
                ("algorithm,a", po::value<std::string>(&algorithm)->required(), "Algoritmos: EfficientHAC, RestrictedHAC, RandomBOBO, AllGreedySolver, ExSumSimSOBO, ExAnySimSOBO, RandomSOBO, SeqScan, ClusterAndPick, RestrictedHACSpecific")
                ("strategy,s", po::value<std::string>(&strategy)->required(), "Estrategias: RANK_BY_INTRA, RANK_BY_INTRA_INTER, RANK_BY_DENSEST_SUBGRAPH, RANK_BY_INTRA_INTER_TUPLE, RANK_BY_INTRA_INTER_PROPORTIONAL")
                ("budget,b", po::value<double>(&budget)->required(), "Presupuesto > 0")
                ("gamma,g", po::value<double>(&gamma)->required(), "Valor del gamma (0 <= gamma <= 1")
                ("bundles,b", po::value<int>(&numFlakes)->required(), "Cantidad de bundles")
                ("iteration,i", po::value<int>(&maxIter)->required(), "Cantidad máxima de iteraciones")
                ("produce,p", po::value<int>(&toProduce)->required(), "Cantidad de bundles que se produciran antes de la selección (solo para BOBO)")
                ("write,w", po::value<bool>(&writeToFile)->required(), "Escribir las soluciones en archivos")
                ("print,r", po::value<bool>(&printToScreen)->required(), "Mostrar por pantalla las soluciones")
                ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return false;
        }
        if (vm.count("version")) {
            std::cout<< version << std::endl;
            return false;
        }
        po::notify(vm);
    }
    catch(std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << errorMsg << std::endl;
        return false;
    }
    catch(...) {
        std::cerr << "Unknown error!" << std::endl;
        std::cerr << errorMsg << std::endl;
        return false;
    }
    return true;
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

int main(int argc, char **argv)
{
    int option;
    std::string element;
    std::string algorithm;
    std::string strategy;
    double budget;
    double gamma;
    int numFlakes;
    int maxIter;
    int toProduce;
    bool writeToFile;
    bool printToScreen;

    bool result = processCommandLine(argc, argv, option, element, algorithm, strategy, budget, gamma,
                                     numFlakes, maxIter, toProduce, writeToFile, printToScreen);

    if (!result) {
        exit(EXIT_FAILURE);
    }
    else {
        switch (option) {
            case 1:
            {
                std::cout<<"Executing solver ..."<<std::endl;
                executeNew(element, algorithm, strategy, budget, gamma,
                           numFlakes, maxIter, toProduce, writeToFile, printToScreen);
                break;
            }
            case 2:
            {
                std::cout<<"Using internal tests ..."<<std::endl;
                usingTestHardcode();
                break;
            }
            case 3:
            {
                std::cout<<"Calculating the similarity ..."<<std::endl;
                insertSimilarity();
                break;
            }
        }
        exit(EXIT_SUCCESS);
    }
/*
std::cout<<"Calculating the similarity of the specific profile ..."<<std::endl;
std::vector<float> specificProfile = generateVector(argv[2], convertToInt(argv[3]));

 if (!specificProfile.empty()) {
    insertSimilarity(specificProfile);
else {
    std::cerr<<"Error el vector de entrada"<<std::endl;
}
*/
}
