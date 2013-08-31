//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "util/configurationJaks.h"
#include "test/testSuites.h"

void usingTestHardcode();
void usingTestFiles(char *configFileName);

int main(int argc, char *argv[]) {
	std::string errorMsg = "Error. Modo de uso:\ntesis-jaks -f <nombre_archivo_configuracion> (para usar con un archivo de configuracion)\ntesis-jaks -t (para usar con los test internos)\n";
	if (argc <= 1) {
		std::cerr<<errorMsg;
	}
	else {
		if (argv[1][0] != '-') {
			std::cerr<<errorMsg;
		}
		else {
			char option = argv[1][1];
			switch(option) {
				case 'f':
					std::cout<<"Usando el archivo de configuracion ..."<<std::endl;
					usingTestFiles(argv[2]);
					break;
				case 't':
					std::cout<<"Usando los tests internos ..."<<std::endl;
					usingTestHardcode();
					break;
				default:
					std::cerr<<errorMsg;
					break;
			}
		}
	}
	return 0;
}

void usingTestHardcode() {
	//testMatrix();
	//testProblemInstanceFromFiles("../files/");
	//testMetisWrapper();
	//testClustering();
	testClusterAndPickSolver("../files/");
	//testConfiguration(argc, argv);
}

void usingTestFiles(char *configFileName) {
	ConfigurationJaks configFiles = ConfigurationJaks(configFileName);
}
