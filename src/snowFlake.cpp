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
#include <stdexcept>

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

SnowFlake& SnowFlake::operator=(const SnowFlake& snowflake) {
	this->problem_ = snowflake.problem_;
	this->elements_ = new IntSet(*(snowflake.elements_));
	return *this;
}

SnowFlake::~SnowFlake() {
	this->elements_->clear();
	delete this->elements_;
	this->problem_ = 0;
}

bool SnowFlake::operator<(const SnowFlake& snowflake) const {
	return snowflake.getSumIntraCompat() < this->getSumIntraCompat();
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
		Double cost;
		String node;
		cost = this->problem_->getCost(*it);
		node = this->problem_->getNode(*it);
		result.append(" * " + node + (node2name == NULL ? "" : " " + node2name->getNodebyName(node)));
		result.append(" (cost=" + convertToString(cost) + ")\n");
	}
	
	result.append("SIZE             = " + convertToString((int)this->elements_->size()) + "\n");
	result.append("COVERAGE         = " + convertToString(this->getCoverSize()) + "\n");
	result.append("COST             = " + convertToString(this->getCost()) + "\n");
	result.append("MIN_INTRA_COMPAT = " + convertToString(this->getMinCompat()) + "\n");
	result.append("SUM_INTRA_COMPAT = " + convertToString(this->getSumIntraCompat()) + "\n\n");
	return result;
}

Double SnowFlake::getSumIntraCompat() const {
	Double sum = 0.0;
	for (IntSet::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		for (IntSet::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
			if (*it<*it2) {
				sum += this->problem_->getCompat(*it, *it2);
			}
		}
	}
	return sum;
}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector) {
	std::sort(snowFlakesVector.begin(), snowFlakesVector.end());
}

IntSet& SnowFlake::ids() const {
	return *(this->elements_);
}

String SnowFlake::showSolution(std::vector<SnowFlake>& solution,const Id2Str* node2name) {
	String result = "\n";
	int avgCost = 0;
	int avgCover = 0;
	int avgSize = 0;
	int avgSumIntraCompat = 0;
	int solutionsSize = solution.size();
	for (std::vector<SnowFlake>::iterator it = solution.begin(); it != solution.end(); ++it) {
		avgCost += it->getCost();
		avgCover += it->getCoverSize();
		avgSize += it->ids().size();
		avgSumIntraCompat += it->getSumIntraCompat();
		result.append(it->toString(node2name));
	}
	result.append("-------------------------------------------------\n");
	result.append("SOLUTION_SIZE = " + convertToString(solutionsSize) + "\n");
	result.append("AVG_COST = " + convertToString(avgCost / (double) solutionsSize) + "\n");
	result.append("AVG_COVER = " + convertToString(avgCover / (double) solutionsSize) + "\n");
	result.append("AVG_SIZE = " + convertToString(avgSize / (double) solutionsSize) + "\n");
	result.append("AVG_SUM_INTRA_COMPAT = " + convertToString(avgSumIntraCompat / (double) solutionsSize) + "\n");
	
	return result;
}

void SnowFlake::writeSolution(const std::vector<SnowFlake>& solution, String fileName, Double interSimilarityWeight) {
	FileOutput file(fileName.c_str());
	for (std::vector<SnowFlake>::const_iterator itSF = solution.begin(); itSF != solution.end(); ++itSF) {
		for (IntSet::iterator it = itSF->elements_->begin(); it != itSF->elements_->end(); ++it) {
			file << itSF->problem_->getNode(*it) << "\t";
		}
		file << "\n";
	}
	file << SnowFlake::objetiveFunction(solution, interSimilarityWeight);
	file.close();
}

Double SnowFlake::objetiveFunction(const std::vector<SnowFlake>& solution, Double interSimilarityWeight) {
	Double sumIntraCompat = 0.00;
	Double sumOneMinusInter = 0.00;
	for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
		sumIntraCompat += it->getSumIntraCompat();
	}
	for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
		for (std::vector<SnowFlake>::const_iterator it2 = it; it2 != solution.end(); ++it2) {
			sumOneMinusInter += 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
		}
	}
	return ((1.0 - interSimilarityWeight) * sumIntraCompat) + (interSimilarityWeight * sumOneMinusInter);
}
