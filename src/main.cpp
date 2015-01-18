//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

/*
* Forma de uso:
* tesis-jaks -f <nombre_archivo_configuracion> [-l]	(para usar con un archivo de configuracion)
* tesis-jaks -t [-l]					(para usar con los test internos)
* tesis-jaks -s [-l]					(para calcular la similaridad)
* tesis-jaks -h						(para ver el modo de uso)
*
* Use mode:
* tesis-jaks -f <configuration_file_name> [-l]		(to use a configuration file)
* tesis-jaks -t [-l]					(for use with the internal test)
* tesis-jaks -s [-l]					(to calculate the similarity)
* tesis-jaks -h						(to see the use mode)
*/

#include <iostream>
#include "executeSolver.h"
//#include "test/testSuites.h"
#include "util/algorithm/vectornorm.h"
#include "util/system/stringUtilities.h"
#include "util/system/Logger.h"

const std::string useMode = "tesis-jaks -f <configuration_file_name> [-l]\t(to use a configuration file)\ntesis-jaks -t [-l]\t\t\t\t(for use with the internal test)\ntesis-jaks -s [-l]\t\t\t\t(to calculate the similarity)\ntesis-jaks -h\t\t\t\t\t(to see this help)\nThe Argument -l initialize the logger.\nArguments in [] are optional.";
std::string errorMsg = "Bad Arguments. Use -h to see how to use.";

void usingTestHardcode(int argc, char **argv) {
    //testOverLoadFunction();
    //testDB();
    //testMatrix();
    //testProblemInstanceFromFiles("../files/");
    //testMetisWrapper();
    //testClustering();
    //testClusterAndPickSolver("../files/");
    //testConfiguration(argc, argv);
}

void usingTestFiles(char *configFileName) {
    if (configFileName == NULL) {
        //Si no pasa ningun archivo como parametro, termina la ejecucion del programa
        std::cerr<<"Invalid file name"<<std::endl;
        exit(0);
    }
    else {
        ConfigurationJaks configFile = ConfigurationJaks(configFileName);
        execute(configFile);
    }
}

void initializeLogger(std::string filename, Logger::loggerConf aConf, int fileVerbosityLevel, int screenVerbosityLevel) {
    DEBUG_CONF(filename, aConf, fileVerbosityLevel, screenVerbosityLevel);
}

void initializeDefaultLogger(char *log) {
    if (log == NULL) {
        return;
    }
    else {
        if (log[0] != '-') {
                std::cerr<<errorMsg<<std::endl;
        }
        else {

            if (log[1] == 'l') {
                std::cout<<"Starting the logger ..."<<std::endl;
                initializeLogger("jaks_output", Logger::file_on|Logger::screen_on, DBG_DEBUG, DBG_ERROR);
            }
            else {
                std::cerr<<errorMsg<<std::endl;
            }
        }
    }
}

std::vector<float>* generateVector(char *theVector, int dimension) {
    std::vector<float> *vectorProfile = new std::vector<float>();
    std::string separator = "-";
    std::vector<std::string> vectorString;

    stringToVectorSplit(theVector,separator,vectorString);

    for (std::vector<std::string>::const_iterator i = vectorString.begin(); i != vectorString.end(); ++i) {
        vectorProfile->push_back(convertToDouble(*i));
    }

    return vectorProfile;
}

int main(int argc, char *argv[]) {
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
                case 'f': {
                    std::cout<<"Using the configuration file ..."<<std::endl;
                    initializeDefaultLogger(argv[3]);
                    usingTestFiles(argv[2]);
                    break;
                }
                case 't': {
                    std::cout<<"Using internal tests ..."<<std::endl;
                    initializeDefaultLogger(argv[2]);
                    usingTestHardcode(argc, argv);
                    break;
                }
                case 's': {
                    std::cout<<"Calculating the similarity ..."<<std::endl;
                    initializeDefaultLogger(argv[2]);
                    insertSimilarity();
                    break;
                }
                case 'p': {
                    std::cout<<"Calculating the similarity of the specific profile ..."<<std::endl;
                    initializeDefaultLogger(argv[4]);
                    std::vector<float> *specificProfile = generateVector(argv[2], convertToInt(argv[3]));
                    if (specificProfile != NULL) {
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
