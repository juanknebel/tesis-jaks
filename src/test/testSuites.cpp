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

void initDebug(String filename, Logger::loggerConf aConf, int fileVerbosityLevel, int screenVerbosityLevel) {
	DEBUG_CONF(filename, aConf, fileVerbosityLevel, screenVerbosityLevel);
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
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	matrixToCompare.set(1,1,8.0);
	testMatrix.testScalarMultiply(2.0, &matrixToCompare);

	matrix.showMe();
	matrixToCompare.showMe();
}

void testProblemInstance() {
	std::cout << "Test ProblemInstance" << std::endl;
	ProblemInstance* problem = new ProblemInstance(6.66);
	TestingProblemInstance testProblem = TestingProblemInstance();
	testProblem.setProblem(problem);

	delete problem;
}

void testProblemInstanceFromFiles(std::string directory) {
	std::cout << "Test ProblemInstanceFromFiles" << std::endl;
	TestingProblemInstanceFromFiles testProblemFiles(directory);
	testProblemFiles.showTheProblem();
}

void testMetisWrapper() {
	initDebug("jaks_output", Logger::file_on|Logger::screen_on, DBG_DEBUG, DBG_ERROR);
	TestingMetisWrapper metis;
	MatrixConcrete graph = giveMeSymetricMatrix3x3With0InDiagonal();
	metis.testCluster(graph, 2);
}
