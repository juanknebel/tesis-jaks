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
#include <cstdlib>
#include "executeSolver.h"
#include "test/testSuites.h"
#include "util/vectornorm.h"

const std::string useMode = "tesis-jaks -f <configuration_file_name> [-l]\t(to use a configuration file)\ntesis-jaks -t [-l]\t\t\t\t(for use with the internal test)\ntesis-jaks -s [-l]\t\t\t\t(to calculate the similarity)\ntesis-jaks -h\t\t\t\t\t(to see this help)\nThe Argument -l initialize the logger.\nArguments in [] are optional.";
std::string errorMsg = "Bad Arguments. Use -h to see how to use.";

void usingTestHardcode(int argc, char **argv) {
	//testOverLoadFunction();
	testDB();
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
				case 'f':
					std::cout<<"Using the configuration file ..."<<std::endl;
					initializeDefaultLogger(argv[3]);
					usingTestFiles(argv[2]);
					break;
				case 't':
					std::cout<<"Using internal tests ..."<<std::endl;
					initializeDefaultLogger(argv[2]);
					usingTestHardcode(argc, argv);
					break;
				case 's':
					std::cout<<"Calculating the similarity ..."<<std::endl;
					initializeDefaultLogger(argv[2]);
					insertSimilarityOfTheAuthor();
					break;
				case 'h':
					std::cout<<"Use mode:"<<std::endl<<useMode<<std::endl;
					break;
				default:
					std::cerr<<errorMsg<<std::endl;
					break;
			}
		}
	}
    //return EXIT_SUCCESS;
    exit(EXIT_SUCCESS);
}
