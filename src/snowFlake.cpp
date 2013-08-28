/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include <float.h>
#include <algorithm>

Double SnowFlake::getMinCompat() {
	Double minCompat = FLT_MAX;
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		for (IntSet::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
			Double compat = this->problem_->getCompat(*it, *it2);
			if (compat > 0.0 && compat < minCompat) {
				minCompat = compat;
			}
		}
	}
	return minCompat;
}

SnowFlake::SnowFlake() {
	this->elements_ = 0;
	this->problem_ = 0;
}

SnowFlake::SnowFlake(const IntSet& elements, ProblemInstance* problem) {
	this->problem_ = problem;
	this->elements_ = new IntSet(elements);
}

SnowFlake::SnowFlake(const SnowFlake& snowflake){
	this->problem_ = snowflake.problem_;
	this->elements_ = new IntSet(*(snowflake.elements_));
}


SnowFlake::~SnowFlake() {
	delete this->elements_;
}

bool SnowFlake::operator<(const SnowFlake& snowFlake) const {
	return this->getSumIntraCompat() < snowFlake.getSumIntraCompat();
}

Double SnowFlake::getCost() {
	Double sumCosts = 0.00;
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		sumCosts += this->problem_->getCost(*it);
	}
	return sumCosts;
}

int SnowFlake::getCoverSize() {
	IntSet covered;
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		IntSet aSetToInsert = this->problem_->getCover(*it);
		covered.insert(aSetToInsert.begin(), aSetToInsert.end());
	}

	return covered.size();
}

String SnowFlake::toString(const Id2Str& node2name) {

	return "";
}

Double SnowFlake::getSumIntraCompat() const {
	Double sum = 0.0;
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		for (IntSet::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
			sum += this->problem_->getCompat(*it, *it2);
		}
	}
	return sum;
}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector) {
	std::sort(snowFlakesVector.begin(), snowFlakesVector.end());
}

IntSet& SnowFlake::ids() {
	return *(this->elements_);
}

String SnowFlake::showMe() {
	return "";
}

