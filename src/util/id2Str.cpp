/*
 * id2Str.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "id2Str.h"

Id2Str::Id2Str() {
	this->node2name_ = 0;
}

Id2Str::Id2Str(String fileName) {
	this->node2name_ = new Object2ObjectOpenHashMap;
	//TODO: leer el arhivo y agregarlo al mapa
}

Id2Str::~Id2Str() {
	delete this->node2name_;
}

String Id2Str::getNodebyName(String node) {
	return (*(*this).node2name_)[node];
}
