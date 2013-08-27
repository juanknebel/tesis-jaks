/*
 * testingMatrix.h
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#ifndef TESTINGMATRIX_H_
#define TESTINGMATRIX_H_

#include "../matrixConcrete.h"

class TestingMatrix {
private:
	MatrixWrapper *theMatrix_;

public:
	TestingMatrix();
	TestingMatrix(const TestingMatrix& );
	~TestingMatrix();

	void setMatrix(MatrixWrapper* theMatrix);
	void testRows(int rows);
	void testCols(int cols);
	void testMaxValue(int maxValue);
	void testMinValue(int minValue);
	void testGet(int row, int col, Double value);
	void testSet(int row, int col, Double value, Double realValue);
	void testScalarMultiply(Double scalar, MatrixWrapper* theMatrix);
};


#endif /* TESTINGMATRIX_H_ */
