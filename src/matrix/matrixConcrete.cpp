/*
 * matrixConcrete.cpp
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#include <cassert>
#include <algorithm>
#include <functional>
#include <iostream>
#include "matrixConcrete.h"
#include "../util/system/Logger.h"

MatrixConcrete::MatrixConcrete(int rows, int cols) : MatrixWrapper(rows, cols) {
	this->theMatrix_ = new mapped_matrix<Double>(rows, cols);
}

MatrixConcrete::MatrixConcrete(const MatrixConcrete& matrix)  : MatrixWrapper(matrix.getRows(), matrix.getCols()) {
	this->theMatrix_ = new mapped_matrix<Double>(*matrix.theMatrix_);
}

MatrixConcrete::~MatrixConcrete() {
	delete this->theMatrix_;
}

int MatrixConcrete::getRows() const {
	return this->rows_;
}

int MatrixConcrete::getCols() const {
	return this->cols_;
}

Double MatrixConcrete::get(int row, int col) const {
	assert (row < this->rows_);
	assert (col < this->cols_);

	return (*(this->theMatrix_))(row, col);
}

Double MatrixConcrete::getMaxValue() const {
	return this->maxValue_;
}

Double MatrixConcrete::getMinValue() const {
	return this->minValue_;
}

void MatrixConcrete::set(int row, int col, Double value) {
	assert (row < this->rows_);
	assert (col < this->cols_);

	(*(this->theMatrix_))(row, col) = value;

	if (isnan(this->maxValue_)) {
		this->maxValue_ = value;
	}

	if (isnan(this->minValue_)) {
		this->minValue_ = value;
	}

	if (value > this->maxValue_) {
		this->maxValue_ = value;
	}

	if (value < this->minValue_) {
		this->minValue_ = value;
	}
}

void MatrixConcrete::scalarMultiply(Double scalar) {
	(*(this->theMatrix_)) *= scalar;
}

void MatrixConcrete::showMe() {
	std::cout << (*(this->theMatrix_)) << std::endl;
}

int MatrixConcrete::countNonZeros() const {
	int count = 0;
	for (int r = 0; r < this->rows_; ++r) {
		for (int c = 0; c < this->cols_; ++c) {
			count = count + (((*(this->theMatrix_))(r,c) > 0.00) ? 1 : 0);
		}
	}
	return count;
}

void MatrixConcrete::ensureSymmetric() {
	assert (this->cols_ == this->rows_);

	int rows = this->rows_;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < rows; ++c) {
			if (this->get(r,c) < this->get(c,r)) {
				this->set(r,c,this->get(c,r));
			}
		}
	}
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < rows; ++c) {
			if (this->get(r,c) < this->get(c,r)) {
				this->set(r,c,this->get(c,r));
			}
		}
	}
}

Double MatrixConcrete::operator ()(int row, int col) {
	return this->get(row, col);
}
