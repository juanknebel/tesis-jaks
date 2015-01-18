/*
 * id2Str.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "id2Str.h"
#include "../system/stringUtilities.h"

Id2Str::Id2Str() {
	this->node2name_ = 0;
	this->dao_ = 0;
}

Id2Str::Id2Str(std::string fileName) {
	this->node2name_ = new std::map<std::string, std::string>;
    std::ifstream file;
	file.open(fileName.c_str());
    std::string line;
	while(getline(file, line, '\n')) {
		std::vector<std::string> tokens;
		stringToVectorSplit(line, "\t", tokens);
		(*(this->node2name_))[tokens[0]] = tokens[1]; 
	}
	file.close();
}

Id2Str::Id2Str(IdentificationGeneretor* theIdentificator) {
    this->node2name_ = new std::map<std::string, std::string>;
    theIdentificator->fillTheMapping(this->node2name_);
}

Id2Str::~Id2Str() {
	delete this->node2name_;
}

std::string Id2Str::getNodebyName(std::string node) const {
	return (*(this->node2name_))[node];
}
