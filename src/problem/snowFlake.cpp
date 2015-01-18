/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include "../util/system/stringUtilities.h"
#include <float.h>
#include <algorithm>
#include <stdexcept>

double SnowFlake::getMinCompat() {
	double minCompat = FLT_MAX;
	for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		for (std::set<int>::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
			double compat = this->problem_->getCompat(*it, *it2);
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
    this->identificator_ = 0;
}

SnowFlake::SnowFlake(const std::set<int>& elements, ProblemInstance* problem) {
	this->problem_ = problem;
	this->elements_ = new std::set<int>(elements);
    this->identificator_ = 0;
}

SnowFlake::SnowFlake(const SnowFlake& snowflake){
	this->problem_ = snowflake.problem_;
	this->elements_ = new std::set<int>(*(snowflake.elements_));
    this->identificator_ = snowflake.getIdentificator();
}

SnowFlake& SnowFlake::operator=(const SnowFlake& snowflake) {
	this->problem_ = snowflake.problem_;
	this->elements_ = new std::set<int>(*(snowflake.elements_));
    this->identificator_ = snowflake.getIdentificator();
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

double SnowFlake::getCost() {
	double sumCosts = 0.00;
	for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		sumCosts += this->problem_->getCost(*it);
	}
	return sumCosts;
}

int SnowFlake::getCoverSize() {
	std::set<int> covered;
	for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		const std::set<int> *aSetToInsert = this->problem_->getCover(*it);
		covered.insert(aSetToInsert->begin(), aSetToInsert->end());
	}

	return covered.size();
}

std::string SnowFlake::toString(const Id2Str* node2name) {
    std::string result = "";
	for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		double cost;
        std::string node;
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

double SnowFlake::getSumIntraCompat() const {
	double sum = 0.0;
	for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
		for (std::set<int>::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
			if (*it<*it2) {
				sum += this->problem_->getCompat(*it, *it2);
			}
		}
	}
	return sum;
}

double SnowFlake::getSumIntraCompatWithSpecificProfile() const {
    double sum = 0.0;
    for (std::set<int>::iterator it = this->elements_->begin(); it != this->elements_->end(); ++it) {
        for (std::set<int>::iterator it2 = this->elements_->begin(); it2 != this->elements_->end(); ++it2) {
            if (*it<*it2) {
                sum += this->problem_->getCompatWithSpecificProfile(*it, *it2);
            }
        }
    }
    return sum;

}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector) {
	std::sort(snowFlakesVector.begin(), snowFlakesVector.end());
}

std::set<int>& SnowFlake::ids() const {
	return *(this->elements_);
}

std::string SnowFlake::getProblemNode(int aNode) const {
    return this->problem_->getNode(aNode);
}

double SnowFlake::objetiveFunction(const std::vector<SnowFlake>& solution, double interSimilarityWeight) {
	double sumIntraCompat = 0.00;
	double sumOneMinusInter = 0.00;
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

unsigned int SnowFlake::getIdentificator() const {
    return this->identificator_;
}

void SnowFlake::setIdentificator(unsigned int theIdentificator) {
    this->identificator_ = theIdentificator;
}

double SnowFlake::maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake) {
    return aSnowFlake.problem_->maxPairwiseCompatibility(aSnowFlake.ids(), otherSnowFlake.ids());
}
