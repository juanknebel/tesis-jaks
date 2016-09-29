/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include "../util/system/stringUtilities.h"
#include <float.h>

double SnowFlake::getMinCompat() const
{
	double minCompat = FLT_MAX;

	for (std::set<int>::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		for (std::set<int>::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
			double compat = this->problem_->getCompat(*it, *it2);

			if (compat > 0.0 && compat < minCompat) {
				minCompat = compat;
			}
		}
	}

	return minCompat;
}

SnowFlake::SnowFlake()
{
	this->elements_ = std::set<int>();
	this->problem_ = nullptr;
	this->identificator_ = 0;
}

SnowFlake::SnowFlake(const std::set<int>& elements, ProblemInstance* problem)
{
	this->problem_ = problem;
	this->elements_ = std::set<int>(elements);
	this->identificator_ = 0;
}

SnowFlake::SnowFlake(const SnowFlake& snowflake)
{
	this->problem_ = snowflake.problem_;
	this->elements_ = std::set<int>(snowflake.elements_);
	this->identificator_ = snowflake.getIdentificator();
}

SnowFlake& SnowFlake::operator=(const SnowFlake& snowflake)
{
	this->problem_ = snowflake.problem_;
	this->elements_.clear();
	this->elements_ = std::set<int>(snowflake.elements_);
	this->identificator_ = snowflake.getIdentificator();
	return *this;
}

SnowFlake::~SnowFlake()
{
	this->elements_.clear();
	this->problem_ = nullptr;
}

bool SnowFlake::operator<(const SnowFlake& snowflake) const
{
	return snowflake.getSumIntraCompat() < this->getSumIntraCompat();
}

double SnowFlake::getCost() const
{
	double sumCosts = 0.00;

	for (std::set<int>::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		sumCosts += this->problem_->getCost(*it);
	}

	return sumCosts;
}

int SnowFlake::getCoverSize() const
{
	std::set<int> covered;

	for (std::set<int>::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		const std::set<int> *aSetToInsert = this->problem_->getCover(*it);
		covered.insert(aSetToInsert->begin(), aSetToInsert->end());
	}

	return covered.size();
}

double SnowFlake::getSumIntraCompat() const
{
	double sum = 0.0;

	for (std::set<int>::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		for (std::set<int>::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
			if (*it<*it2) {
				sum += this->problem_->getCompat(*it, *it2);
			}
		}
	}

	return sum;
}

double SnowFlake::getSumIntraCompatWithSpecificProfile() const
{
	double sum = 0.0;

	for (std::set<int>::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		for (std::set<int>::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
			if (*it<*it2) {
				sum += this->problem_->getCompatWithSpecificProfile(*it, *it2);
			}
		}
	}

	return sum;

}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector)
{
	std::sort(snowFlakesVector.begin(), snowFlakesVector.end());
}

std::set<int>& SnowFlake::ids() const
{
	return const_cast<std::set<int>&> (this->elements_);
}

std::string SnowFlake::getProblemNode(int aNode) const
{
	return this->problem_->getNode(aNode);
}

double SnowFlake::objetiveFunction(const std::vector<SnowFlake>& solution, double gamma)
{
	double sumIntraCompat = SnowFlake::getIntra(solution);
	double sumOneMinusInter = SnowFlake::getInter(solution);

	return ((1.0 - gamma) * sumIntraCompat) + (gamma * sumOneMinusInter);
}

double SnowFlake::getIntra(const std::vector<SnowFlake> &solution)
{
	double sumIntraCompat = 0.00;

	for (auto aFlake : solution) {
		sumIntraCompat += (aFlake.ids().size() > 0) ? aFlake.getSumIntraCompat() : 0;
	}

	return sumIntraCompat;
}

double SnowFlake::getInter(const std::vector<SnowFlake> &solution)
{
	double sumOneMinusInter = 0.00;

	for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
		if (it->ids().size() > 0) {
			for (std::vector<SnowFlake>::const_iterator it2 = it; it2 != solution.end(); ++it2) {
				if (it2->ids().size() > 0) {
					sumOneMinusInter += 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
				}
			}
		}
	}

	return sumOneMinusInter;
}

int SnowFlake::getIdentificator() const
{
	return this->identificator_;
}

void SnowFlake::setIdentificator(int theIdentificator)
{
	this->identificator_ = theIdentificator;
}

double SnowFlake::maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake)
{
	return aSnowFlake.problem_->maxPairwiseCompatibility(aSnowFlake.ids(), otherSnowFlake.ids());
}

std::ostream& operator<< (std::ostream& stream, const SnowFlake& snowFlake)
{
    int i = 1, count = snowFlake.ids().size();
	for (auto anElement : snowFlake.ids()) {
        if (i == count) {
            stream << anElement;
        } else {
        stream << anElement << ",";
        }
        i++;
	}
	return stream;
}

double SnowFlake::getCostNode(int aNode) const {
	return this->problem_->getCost(aNode);
}
