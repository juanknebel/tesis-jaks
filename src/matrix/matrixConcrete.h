/*
 * matrixConcrete.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef MATRIXCONCRETE_H_
#define MATRIXCONCRETE_H_

#include "matrixWrapper.h"
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

class MatrixConcrete : public MatrixWrapper {
private:
    mapped_matrix<double> *theMatrix_;

public:
	MatrixConcrete(int rows, int cols);
	MatrixConcrete(const MatrixConcrete& matrix);
	~MatrixConcrete();

	int getRows() const;
	int getCols() const;
    double get(int row, int col) const;
    double getMaxValue() const;
    double getMinValue() const;
    void set(int row, int col, double value);
    void scalarMultiply(double scalar);
	void showMe();
	int countNonZeros() const;
	void ensureSymmetric();
    double operator()(int row, int col);
};

#endif /* MATRIXCONCRETE_H_ */
