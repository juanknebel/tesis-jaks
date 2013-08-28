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

MatrixConcrete::MatrixConcrete(int rows, int cols) : MatrixWrapper(rows, cols) {
	this->theVector_ = new DblVector (this->rows_ * this->cols_);
}

MatrixConcrete::MatrixConcrete(const MatrixConcrete& matrix)  : MatrixWrapper(matrix.getRows(), matrix.getCols()) {
	this->theVector_ = new DblVector (this->rows_ * this->cols_);
	std::copy(matrix.theVector_->begin(), matrix.theVector_->end(), this->theVector_->begin());
}

MatrixConcrete::~MatrixConcrete() {
	delete this->theVector_;
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

	return this->theVector_->at(row * this->cols_ + col);
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

	this->theVector_->at(row * this->cols_ + col) = value;

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
	for (int i = 0; i < this->rows_ * this->cols_; ++i) {
		this->theVector_->at(i) = this->theVector_->at(i) * scalar;
	}
}

void MatrixConcrete::showMe() {
	for (int i = 0; i < this->rows_ * this->cols_; ++i) {
		std::cout<<this->theVector_->at(i)<<" ";
		if ((i + 1) % this->cols_ == 0) {
			std::cout<<std::endl;
		}
	}
}

int MatrixConcrete::countNonZeros() const {
	int count = 0;
	for (int i = 0; i < this->rows_ * this->cols_; ++i) {
		count = count + ((this->theVector_->at(i) > 0.00) ? 1 : 0);
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
