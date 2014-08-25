/*
 * id2Str.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "id2Str.h"
#include "stringUtilities.h"

Id2Str::Id2Str() {
	this->node2name_ = 0;
	this->dao_ = 0;
}

Id2Str::Id2Str(String fileName) {
	this->node2name_ = new MapStringString;
	FileInput file;
	file.open(fileName.c_str());
	String line;
	while(getline(file, line, '\n')) {
		StrVector tokens;
		stringToVectorSplit(line, "\t", tokens);
		(*(this->node2name_))[tokens[0]] = tokens[1]; 
	}
	file.close();
}

Id2Str::Id2Str(IdentificationGeneretor* theIdentificator) {
    theIdentificator->fillTheMapping(this->node2name_);
}

Id2Str::~Id2Str() {
	delete this->node2name_;
}

String Id2Str::getNodebyName(String node) const {
	return (*(this->node2name_))[node];
}
