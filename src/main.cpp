//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

/*
* Forma de uso: 
* tesis-jaks -f <nombre_archivo_configuracion> (para usar con un archivo de configuracion)
* tesis-jaks -t                                (para usar con los test internos)
*/

#include <iostream>
#include <cstdlib>
#include "executeSolver.h"
#include "test/testSuites.h"

void usingTestHardcode(int argc, char *argv[]);
void usingTestFiles(char *configFileName);

void initializeDebug(std::string filename, Logger::loggerConf aConf, int fileVerbosityLevel, int screenVerbosityLevel) {
	DEBUG_CONF(filename, aConf, fileVerbosityLevel, screenVerbosityLevel);
}

void initializeDefaultDebug() {
	initializeDebug("jaks_output", Logger::file_on|Logger::screen_on, DBG_DEBUG, DBG_ERROR);
}

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
					usingTestHardcode(argc, argv);
					break;
				default:
					std::cerr<<errorMsg;
					break;
			}
		}
	}
	return 0;
}

void usingTestHardcode(int argc, char *argv[]) {
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
		std::cerr<<"Nombre de archivo invalido"<<std::endl;
		return;
	}
	
	ConfigurationJaks configFiles = ConfigurationJaks(configFileName);
	if (atoi(configFiles["log"].c_str())) {
		//Si esta en modo debug, inicia el Logger
		initializeDefaultDebug();
	}
	
	switch(atoi(configFiles["SOLVER"].c_str())) {
		case ClusterAndPick:
			std::cout<<"Ejecutando ClusterAndPickSolver ..."<<std::endl;
			executeClusterAndPickSolver(configFiles);
			break;
		case RestrictedHAC:
			std::cout<<"Ejecutando RestrictedHACSolver ..."<<std::endl;
			executeRestrictedHACSolver(configFiles);
			break;
		case RestrictedHACSpecific:
			std::cout<<"Ejecutando RestrictedHACSpecificSolver ..."<<std::endl;
			executeRestrictedHACSpecificSolver(configFiles);
			break;
		case RandomBOBO:
			std::cout<<"Ejecutando RandomBOBOSolver ..."<<std::endl;
			executeRandomBOBOSolver(configFiles);
			break;
		case RandomSOBO:
			std::cout<<"Ejecutando RandomSOBOSolver ..."<<std::endl;
			executeRandomSOBOSolver(configFiles);
			break;
		case ExAnySimSOBO:
			std::cout<<"Ejecutando ExhaustiveGreedyAnySimSolver ..."<<std::endl;
			executeExhaustiveGreedyAnySimSolver(configFiles);
			break;
		case ExSumSimSOBO:
			std::cout<<"Ejecutando ExhaustiveGreedySumSimSolver ..."<<std::endl;
			executeExhaustiveGreedySumSimSolver(configFiles);
			break;
		default:
			std::cerr<<"El metodo elegido para la resolucion no existe"<<std::endl;
			break;
	}
}
