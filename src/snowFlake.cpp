/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include "util/stringUtilities.h"
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
		const IntSet *aSetToInsert = this->problem_->getCover(*it);
		covered.insert(aSetToInsert->begin(), aSetToInsert->end());
	}

	return covered.size();
}

String SnowFlake::toString(const Id2Str* node2name) {
	String result = "";
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		result.append(" * " + convertToString(*it) + (node2name == NULL ? "" : " " + node2name->getNodebyName(this->problem_->getNode(*it))));
		result.append(" (cost=" + convertToString(this->problem_->getCost(*it)) + ")\n");
	}
	result.append(" SIZE             = " + convertToString((int)this->elements_->size()) + "\n");
	result.append(" COVERAGE         = " + convertToString(this->getCoverSize()) + "\n");
	result.append(" COST             = " + convertToString(this->getCost()) + "\n");
	result.append(" MIN_INTRA_COMPAT = " + convertToString(this->getMinCompat()) + "\n");
	result.append(" SUM_INTRA_COMPAT = " + convertToString(this->getSumIntraCompat()) + "\n");
	return result;
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

String SnowFlake::showSolution(std::vector<SnowFlake>& solutions) {
	String result;
	int avgCost = 0;
	int avgCover = 0;
	int avgSize = 0;
	int avgSumIntraCompat = 0;
	int solutionsSize = solutions.size();
	for (std::vector<SnowFlake>::iterator it = solutions.begin(); it != solutions.end(); ++it) {
		avgCost += it->getCost();
		avgCover += it->getCoverSize();
		avgSize += it->ids().size();
		avgSumIntraCompat += it->getSumIntraCompat();
	}
	result = "SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n";
	result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + "\n");
	result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + "\n");
	result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + "\n");
	result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + "\n");
	
	return result;
}
