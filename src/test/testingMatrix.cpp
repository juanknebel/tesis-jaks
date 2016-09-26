/*
 * testingMatrix.cpp
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#include <iostream>
#include "testingMatrix.h"

TestingMatrix::TestingMatrix()
{
	this->theMatrix_ = 0;
}

TestingMatrix::~TestingMatrix()
{
	delete this->theMatrix_;
}

MatrixWrapper* TestingMatrix::getMatrix()
{
	return this->theMatrix_;
}

void TestingMatrix::setMatrix(MatrixWrapper* theMatrix)
{
	if (this->theMatrix_ != 0) {
		delete this->theMatrix_;
	}

	MatrixConcrete* theNewmatrix =  dynamic_cast<MatrixConcrete*> (theMatrix);
	this->theMatrix_ = new MatrixConcrete(*theNewmatrix);
}

void TestingMatrix::testRows(int rows)
{
	if (this->theMatrix_->getRows() == rows) {
		std::cout<<"Filas funciono"<<std::endl;
	}

	else {
		std::cout<<"Filas fallo"<<std::endl;
	}
}
void TestingMatrix::testCols(int cols)
{
	if (this->theMatrix_->getCols() == cols) {
		std::cout<<"Columnas funciono"<<std::endl;
	}

	else {
		std::cout<<"Columnas fallo"<<std::endl;
	}
}

void TestingMatrix::testMaxValue(int maxValue)
{
	if (this->theMatrix_->getMaxValue() == maxValue) {
		std::cout<<"Maximo valor funciono"<<std::endl;
	}

	else {
		std::cout<<"Maximo valor fallo"<<std::endl;
	}
}

void TestingMatrix::testMinValue(int minValue)
{
	if (this->theMatrix_->getMinValue() == minValue) {
		std::cout<<"Minimo valor funciono"<<std::endl;
	}

	else {
		std::cout<<"Minimo valor fallo"<<std::endl;
	}
}

void TestingMatrix::testGet(int row, int col, double value)
{
	if (this->theMatrix_->get(row, col) == value) {
		std::cout<<"Obtener un elemento funciono"<<std::endl;
	}

	else {
		std::cout<<"Obtener un elemento fallo"<<std::endl;
	}
}

void TestingMatrix::testSet(int row, int col, double value, double realValue)
{
	this->theMatrix_->set(row, col, value);

	if (this->theMatrix_->get(row, col) == realValue) {
		std::cout<<"Asignar un elemento funciono"<<std::endl;
	}

	else {
		std::cout<<"Asignar un elemento fallo"<<std::endl;
	}
}

void TestingMatrix::testScalarMultiply(double scalar, MatrixWrapper* theMatrix)
{
	this->theMatrix_->scalarMultiply(scalar);
	bool notFail = true;

	for (int i = 0; i < this->theMatrix_->getRows(); ++i) {
		for (int j = 0; j < this->theMatrix_->getCols(); ++j) {
			notFail = notFail && this->theMatrix_->get(i,j) == theMatrix->get(i,j);
		}
	}

	if (notFail) {
		std::cout<<"Multiplicar por un escalar funciono"<<std::endl;
	}

	else {
		std::cout<<"Multiplicar por un escalar fallo"<<std::endl;
	}
}

void TestingMatrix::testCountNonZeros(int cantOfNonZero)
{
	if (this->theMatrix_->countNonZeros() == cantOfNonZero) {
		std::cout<<"Contar la cantidad de elementos que no son ceros funciono"<<std::endl;
	}

	else {
		std::cout<<"Contar la cantidad de elementos que no son ceros fallo"<<std::endl;
	}
}
