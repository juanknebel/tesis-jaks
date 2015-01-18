/*
 * matrixWrapper.h
 *
 *  Created on: 13/07/2013
 *      Author: zero
 */

#ifndef MATRIXWRAPPER_H_
#define MATRIXWRAPPER_H_

#include <cmath>

class MatrixWrapper {
protected:
    double maxValue_;
    double minValue_;
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
    virtual double get(int row, int col) const = 0;
    virtual double getMaxValue() const = 0;
    virtual double getMinValue() const = 0;
    virtual void set(int row, int col, double value) = 0;
    virtual void scalarMultiply(double scalar) = 0;
	virtual void showMe() = 0;
	virtual int countNonZeros() const = 0;
	virtual void ensureSymmetric() = 0;
    virtual double operator()(int row, int col) = 0;
};


#endif /* MATRIXWRAPPER_H_ */
