/*
 * id2Str.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "id2Str.h"

Id2Str::Id2Str()
{
}

Id2Str::~Id2Str()
{
}

std::string Id2Str::getNodebyName(std::string node) const
{
	return (*(this->node2name_.get()))[node];
}

Id2Str::Id2Str(const Element *element, Dao* dao)
{
	this->node2name_ = std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>);
	element->completeMapping(*this->node2name_.get(), nullptr);
}
