/*
 * matrixWrapper.h
 *
 *  Created on: 13/07/2013
 *      Author: zero
 */

#ifndef MATRIXWRAPPER_H_
#define MATRIXWRAPPER_H_

#include <cmath>
#include "util/redefinitions.h"

class MatrixWrapper {
protected:
	Double maxValue_;
	Double minValue_;
	int rows_;
	int cols_;

public:
	MatrixWrapper(int rows, int cols) {
		this->maxValue_ = NAN;
		this->minValue_ = NAN;
		this->rows_ = rows;
		this->cols_ = cols;
	}
	virtual ~MatrixWrapper() {}

	virtual int getRows() const = 0;
	virtual int getCols() const = 0;
	virtual Double get(int row, int col) const = 0;
	virtual Double getMaxValue() const = 0;
	virtual Double getMinValue() const = 0;
	virtual void set(int row, int col, Double value) = 0;
	virtual void scalarMultiply(Double scalar) = 0;
	virtual void showMe() = 0;
	virtual int countNonZeros() const = 0;
	virtual void ensureSymmetric() = 0;
	virtual Double operator()(int row, int col) = 0;
};


#endif /* MATRIXWRAPPER_H_ */
