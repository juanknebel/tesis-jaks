/*
 * matrixConcrete.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef MATRIXCONCRETE_H_
#define MATRIXCONCRETE_H_

#include "matrixWrapper.h"
#include "util/redefinitions.h"

class MatrixConcrete : public MatrixWrapper {
private:
	DblVector *theVector_;
public:
	MatrixConcrete(int rows, int cols);
	MatrixConcrete(const MatrixConcrete& matrix);
	~MatrixConcrete();

	int getRows() const;
	int getCols() const;
	Double get(int row, int col) const;
	Double getMaxValue() const;
	Double getMinValue() const;
	void set(int row, int col, Double value);
	void scalarMultiply(Double scalar);
	void showMe();
	int countNonZeros() const;
	void ensureSymmetric();
};

#endif /* MATRIXCONCRETE_H_ */
