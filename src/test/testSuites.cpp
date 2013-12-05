/*
 * testSuites.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include <iostream>
#include "testSuites.h"
#include "testingMatrix.h"
#include "testingProblemInstance.h"
#include "testingProblemInstanceFromFiles.h"
#include "testingMetisWrapper.h"
#include "testingClustering.h"
#include "testingClusterAndPickSolver.h"
#include "../problemInstanceFromDataBase.h"
#include "../util/configurationJaks.h"
#include "../dao/daoMySql.h"
#include "../util/dbConnection.h"

MatrixConcrete giveMeMatrix2x2(Double a, Double b, Double c, Double d) {
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,a);
	matrix.set(0,1,b);
	matrix.set(1,0,c);
	matrix.set(1,1,d);
	return matrix;
}

MatrixConcrete giveMeMatrix2x2() {
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,4.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix2x2() {
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,2.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix2x2With0InDiagonal() {
	MatrixConcrete matrix(2,2);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(1,0,3.0);
	matrix.set(1,1,0.0);
	return matrix;
}

MatrixConcrete giveMeMatrix3x3() {
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,4.0);
	matrix.set(1,1,5.0);
	matrix.set(1,2,6.0);
	matrix.set(2,0,7.0);
	matrix.set(2,1,8.0);
	matrix.set(2,2,9.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix3x3() {
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,1.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,2.0);
	matrix.set(1,1,1.0);
	matrix.set(1,2,2.0);
	matrix.set(2,0,3.0);
	matrix.set(2,1,2.0);
	matrix.set(2,2,1.0);
	return matrix;
}

MatrixConcrete giveMeMatrix3x3With0InDiagonal() {
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,4.0);
	matrix.set(1,1,0.0);
	matrix.set(1,2,6.0);
	matrix.set(2,0,7.0);
	matrix.set(2,1,8.0);
	matrix.set(2,2,0.0);
	return matrix;
}

MatrixConcrete giveMeSymetricMatrix3x3With0InDiagonal() {
	MatrixConcrete matrix(3,3);
	matrix.set(0,0,0.0);
	matrix.set(0,1,2.0);
	matrix.set(0,2,3.0);
	matrix.set(1,0,2.0);
	matrix.set(1,1,0.0);
	matrix.set(1,2,2.0);
	matrix.set(2,0,3.0);
	matrix.set(2,1,2.0);
	matrix.set(2,2,0.0);
	return matrix;
}

ProblemInstanceFromFiles* giveMeProblemInstance(std::string directory) {
	std::string fileNodeCompatibility = directory + "node_compatibility.csv";
	std::string fileNodeCost = directory + "node_cost.csv";
	std::string fileNodeCover = directory + "node_cover.csv";
	std::string fileNodeName = directory + "node_name.csv";
	std::string fileTypeName = directory + "type_name.csv";
	ProblemInstanceFromFiles* result = new ProblemInstanceFromFiles(fileNodeCost, fileNodeCompatibility, fileNodeCover, 1000.00);
	return result;
}

ProblemInstance* giveMeAnotherProblemInstance(std::string directory) {
	std::string fileNodeCompatibility = directory + "node_compatibility.csv";
	std::string fileNodeCost = directory + "node_cost.csv";
	std::string fileNodeCover = directory + "node_cover.csv";
	std::string fileNodeName = directory + "node_name.csv";
	std::string fileTypeName = directory + "type_name.csv";
	ProblemInstance* result = new ProblemInstanceFromFiles(fileNodeCost, fileNodeCompatibility, fileNodeCover, 1000.00);
	return result;
}

void initDebug(String filename, Logger::loggerConf aConf, int fileVerbosityLevel, int screenVerbosityLevel) {
	DEBUG_CONF(filename, aConf, fileVerbosityLevel, screenVerbosityLevel);
}

void initDefaultDebug() {
	initDebug("jaks_output", Logger::file_on|Logger::screen_on, DBG_DEBUG, DBG_ERROR);
}

void configureFile(char* fileName) {
	String value;
	ConfigurationJaks configFiles = ConfigurationJaks(fileName);
	while(true) {
		std::cout<<"Ingresar la clave a consultar (X para salir) ";
		std::cin>>value;
		if (value == "X") {
			break;
		}
	std::cout<<"EL valor de la clave es: "<<configFiles.giveMeValue(value)<<std::endl;
	}
}

void testDBGeneric(Dao& dao, String tableName) {
	if (dao.isConnected()) {
		bool hasresult = dao.executeSelectAllFrom(tableName);
		if (hasresult) {
			const char** result;
			int numOffields = dao.getNumberOfFields();
			while(result = dao.getNextRow()) {
				for (int i=0;i<numOffields;++i) {
					if (result[i] != NULL) {
						std::cout<<result[i];
					}
					else {
						std::cout<<"NULL";
					}
					if (i!=numOffields-1) {
						std::cout<<"|";
					}
				}
				std::cout<<std::endl;
			}
		}
		else {
			std::cerr<<"Error al obtener resutlados"<<std::endl;
			std::cerr<<dao.getError()<<std::endl;
		}
	}
	else {
		std::cerr<<"Error no esta conectado a ninguna base de datos"<<std::endl;
	}
}

void testDBCitationInformation(Dao& dao) {
	testDBGeneric(dao,"CitationInformation");
}

void testDBARTICLES(Dao& dao) {
	testDBGeneric(dao,"ARTICLES");
}

void testDB1() {
	Dao *dao = new DaoMySql(db_database,db_user,db_password,db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao->getError()<<std::endl;
	}
	else {
		std::cout<<dao->showConnection();
		testDBARTICLES(*dao);
		dao->disconnect();
	}
	
	connect = dao->connect();
	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao->getError()<<std::endl;
	}
	else {
		std::cout<<dao->showConnection();
		testDBCitationInformation(*dao);
		dao->disconnect();
	}
	delete dao;
}

void testDBCustomQuery() {
	Dao *dao = new DaoMySql(db_database,db_user,db_password,db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao->getError()<<std::endl;
	}
	else {
		std::cout<<dao->showConnection();
		if (dao->isConnected()) {
			dao->showConnection();
			//bool hasresult = dao->executeCustomConsultativeQuery("select distribution_KEY from TopicProfile_distribution group by distribution_KEY order by distribution_KEY asc");
			bool hasresult = dao->executeCustomConsultativeQuery("select count(*) from ARTICLES");
			if (hasresult) {
				const char** result;
				int numOffields = dao->getNumberOfFields();
				while(result = dao->getNextRow()) {
					for (int i=0;i<numOffields;++i) {
						if (result[i] != NULL) {
							std::cout<<result[i];
						}
						else {
							std::cout<<"NULL";
						}
						if (i!=numOffields-1) {
							std::cout<<"|";
						}
					}
					std::cout<<std::endl;
				}
			}
			else {
				std::cerr<<"Error al obtener resutlados"<<std::endl;
				std::cerr<<dao->getError()<<std::endl;
			}
		}
		else {
			std::cerr<<"Error no esta conectado a ninguna base de datos"<<std::endl;
		}
	}
	delete dao;
}

void testDBInsertCustom() {
	Dao *dao = new DaoMySql("test",db_user,db_password,db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao->getError()<<std::endl;
	}
	else {
		std::cout<<dao->showConnection();
		if (dao->isConnected()) {
			bool isOk = dao->executeCustomModifiableQuery("insert into tablaPrueba values (3,5,\'prueba tres\')");
			if (!isOk) {
				std::cerr<<dao->getError()<<std::endl;
			}
		}
	}
	delete dao;
}

void testDBInsertPartial() {
	Dao *dao = new DaoMySql("test",db_user,db_password,db_server);
	bool connect = dao->connect();
	if (!connect) {
		std::cerr<<"Error al conectarse a la base de datos"<<std::endl;
		std::cerr<<dao->getError()<<std::endl;
	}
	else {
		std::cout<<dao->showConnection();
		if (dao->isConnected()) {
			const char *fields [] =  {"id", "descripcion", "valor"};
			const char *values [] = {"6", "\'prueba seis\'", "333"};
			bool isOk = dao->executeInsertQueryWithValues("tablaPrueba", fields, values, 3);
			if (!isOk) {
				std::cerr<<dao->getError()<<std::endl;
			}
		}
	}
	delete dao;
}

void testOverLoadFunction() {
	Dao *dao = new DaoMySql(db_database, db_user, db_password,db_server);
	ProblemInstance *problem = new ProblemInstanceFromDataBase(dao,"tab","tab","tab","tab","tab","tab", "tab","tab",5);
	std::cout<<problem->getCompat(1,1)<<std::endl;
	delete dao;
	delete problem;
}

void testDB() {
	initDefaultDebug();
	testDBCustomQuery();
	//testDBInsertPartial();
}

void testMatrix() {
	std::cout << "Test MatrixWrapper y MatrixConcrete" << std::endl;
	MatrixConcrete matrix = giveMeMatrix2x2(1.0,2.0,3.0,4.0);

	TestingMatrix testMatrix = TestingMatrix();
	testMatrix.setMatrix(&matrix);

	MatrixConcrete matrixToCompare = giveMeMatrix2x2(1.0,2.0,3.0,4.0);

	testMatrix.testRows(2);
	testMatrix.testCols(2);
	testMatrix.testMinValue(1.0);
	testMatrix.testMaxValue(4.0);
	testMatrix.testGet(1,0,3.0);

	testMatrix.testSet(1,1,66.6,66.6);

	matrixToCompare.set(0,0,2.0);
	matrixToCompare.set(0,1,4.0);
	matrixToCompare.set(1,0,6.0);

	matrixToCompare.set(1,1,133.2);
	testMatrix.getMatrix()->showMe();
	matrixToCompare.showMe();
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	matrixToCompare.set(1,1,8.0);
	testMatrix.getMatrix()->showMe();
	matrixToCompare.showMe();
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	MatrixConcrete anotherMatrix = giveMeMatrix2x2(0.0,0.0,0.0,0.0);
	testMatrix.setMatrix(&anotherMatrix);

	testMatrix.getMatrix()->showMe();
	testMatrix.testCountNonZeros(0);
	testMatrix.getMatrix()->showMe();
	testMatrix.testCountNonZeros(2);
}

void testProblemInstance() {
	std::cout << "Test ProblemInstance" << std::endl;
	ProblemInstance* problem = new ProblemInstance(6.66);
	TestingProblemInstance testProblem = TestingProblemInstance();
	testProblem.setProblem(problem);

	delete problem;
}

void testProblemInstanceFromFiles(std::string directory) {
	initDefaultDebug();
	std::cout << "Test ProblemInstanceFromFiles" << std::endl;
	TestingProblemInstanceFromFiles testProblemFiles(directory);
	testProblemFiles.showTheProblem();
}

void testMetisWrapper() {
	initDefaultDebug();
	TestingMetisWrapper metis;
	MatrixConcrete graph = giveMeSymetricMatrix3x3With0InDiagonal();
	metis.testCluster(graph, 2);
}

void testClustering() {
	TestingClustering clustering;
	MatrixConcrete graphNoSymetric = giveMeMatrix3x3With0InDiagonal();
	MatrixConcrete graphSymetric = giveMeSymetricMatrix3x3With0InDiagonal();
	clustering.testCluster(graphSymetric, 2);
	clustering.testSymmetrizeCluster(graphNoSymetric, 2);
}

void testClusterAndPickSolver ( std::string directory) {
	initDefaultDebug();
	ProblemInstance* anotherProblem = giveMeAnotherProblemInstance(directory);
	TestingClusterAndPickSolver anotherClusterPickSolver(*anotherProblem);
	anotherClusterPickSolver.testingSolve(4);
}

void testConfiguration(int argc, char *argv[]) {
	if (argc <= 1) {
		std::cerr<<"Error. Modo de uso:\ntesis-jaks -f <nombre_archivo_configuracion>"<<std::endl;
	}
	else {
		if (argv[1][0] != '-') {
			std::cerr<<"Error. Modo de uso:\ntesis-jaks -f <nombre_archivo_configuracion>"<<std::endl;
		}
		else {
			char option = argv[1][1];
			switch(option) {
				case 'f':
					std::cout<<"Usando el archivo de configuracion ..."<<std::endl;
					configureFile(argv[2]);
					break;
				case 't':
					std::cout<<"Usando los tests internos ..."<<std::endl;
					break;
				default:
					std::cerr<<"Error. Modo de uso:\ntesis-jaks -f <nombre_archivo_configuracion>"<<std::endl;
					break;
			}
		}
	}
}
