/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include "snowFlakeHelper.h"

SnowFlake::SnowFlake() {
    this->identificator_ = -1;
}

SnowFlake::SnowFlake(std::unique_ptr<std::set<int>> elements) {
	this->elements_.reset();
	this->elements_ = std::move(elements);
    this->identificator_ = -1;
}

SnowFlake::SnowFlake(const SnowFlake& snowflake){
	this->elements_.reset();
	this->elements_ = std::move(new std::set<int>(snowflake.ids()));
    this->identificator_ = snowflake.getIdentificator();
}

SnowFlake& SnowFlake::operator=(const SnowFlake& snowflake) {
	this->elements_.reset();
	this->elements_ = std::move(new std::set<int>(snowflake.ids()));
    this->identificator_ = snowflake.getIdentificator();
	return *this;
}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector, ProblemInstance& problem) {
	SnowFlakeHelper snowFlakeHelper;
	//TODO: pasarle la funcion que compara
	//std::sort(snowFlakesVector.begin(), snowFlakesVector.end(), snowFlakeHelper.getSumIntraCompat(problem));
}

std::set<int>& SnowFlake::ids() const {
	return *(this->elements_);
}

unsigned int SnowFlake::getIdentificator() const {
    return this->identificator_;
}

void SnowFlake::setIdentificator(unsigned int theIdentificator) {
    this->identificator_ = theIdentificator;
}
