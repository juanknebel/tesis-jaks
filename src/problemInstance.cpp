/*
 * problemInstance.cpp
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#include "problemInstance.h"
#include "util/stringUtilities.h"
#include <cassert>

ProblemInstance::ProblemInstance() {
	this->budget_ = NAN;
	this->nodeCost_ = 0;
	this->nodeCover_ = 0;
	this->nodeCompat_ = 0;
	this->node2id_ = 0;
	this->id2node_ = 0;
}

ProblemInstance::ProblemInstance(Double budget) {
	this->budget_ = budget;
	this->nodeCost_ = new Int2DoubleOpenHashMap;
	this->nodeCover_ = new Int2ObjectOpenHashMap;
	this->nodeCompat_ = 0;
	this->node2id_ = new Object2IntOpenHashMap;
	this->id2node_ = new Int2ObjectOpenHashMapString;
}

ProblemInstance::~ProblemInstance() {
	delete this->nodeCost_;
	for (Int2ObjectOpenHashMap::iterator it = this->nodeCover_->begin(); it != this->nodeCover_->end(); ++it) {
		it->second->clear();
	}
	this->nodeCover_->clear();
	delete this->nodeCover_;
	delete this->nodeCompat_;
}

IntSet& ProblemInstance::getIds() {
	IntSet *aSetOfIds = new IntSet;
	for (Int2DoubleOpenHashMap::iterator it = this->nodeCost_->begin(); it != this->nodeCost_->end(); ++it) {
		aSetOfIds->insert(it->first);
	}
	return *aSetOfIds;
}

int ProblemInstance::numNodes() {
	return this->nodeCost_->size();
}

Double ProblemInstance::getCost(int id) {
	return this->nodeCost_->at(id);
}

Double ProblemInstance::getbudget() {
	return this->budget_;
}

const IntSet* ProblemInstance::getCover(int id) {
	return this->nodeCover_->at(id);
}

Double ProblemInstance::getCompat(int id1, int id2) {
	assert (id1 < this->nodeCompat_->getRows());
	assert (id2 < this->nodeCompat_->getCols());
	return this->nodeCompat_->get(id1, id2);
}

SparseDoubleMatrix2D* ProblemInstance::getCompat() {
	return this->nodeCompat_;
}

void ProblemInstance::normalizeNodeCompat() {
	Double maxValue = this->nodeCompat_->getMaxValue();
	this->nodeCompat_->scalarMultiply(1.0/maxValue);
}

String ProblemInstance::getNode(int id) {
	return this->id2node_->at(id);
}

int ProblemInstance::getId(String node) {
	return this->node2id_->at(node);
}

Double ProblemInstance::maxPairwiseCompatibility(const IntSet& aSet, const IntSet& otherSet) {
	Double maxCompatibility = 0.0;
	for (IntSet::iterator it1 = aSet.begin(); it1 != aSet.end(); ++it1) {
		for (IntSet::iterator it2 = otherSet.begin(); it2 != otherSet.end(); ++it2){
			int n1 = (int) *it1;
			int n2 = (int) *it2;
			Double compatValue = this->getCompat(n1, n2);
			if (compatValue > maxCompatibility) {
				maxCompatibility = compatValue;
			}
		}
	}
	return maxCompatibility;
}

/*Double ProblemInstance::maxPairwiseCompatibility(const SnowFlake& aSnow, const SnowFlake& otherSnow) {
	return this->maxPairwiseCompatibility(aSnow.ids(), otherSnow.ids());
}*/

void ProblemInstance::createIdNodeMappings(StrVector nodes) {
	int nextId = 0;
	for (StrVector::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		String nodeId(*it);
		(*(*this).node2id_)[nodeId]=nextId;
		(*(*this).id2node_)[nextId]=nodeId;
		++nextId;
	}
}

String ProblemInstance::showMe() {
	String result;
	result = this->showBudget();
	result.append(this->showCosts());
	result.append(this->showCompat());
	result.append(this->showCover());
	return result;
}

String ProblemInstance::showBudget() {
	String result;
	result = "----------------------El presupuesto---------------------------------\n";
	result.append(convertToString(this->budget_) + "\n");
	result.append("---------------------------------------------------------------------\n");
	return result;
}

String ProblemInstance::showCosts() {
	String result;
	result = "-----------------------Nodo, Costo-----------------------------------\n";
	for(Int2DoubleOpenHashMap::iterator it = this->nodeCost_->begin(); it != this->nodeCost_->end(); ++it) {
		result.append(this->getNode(it->first) + ", " + convertToString(it->second) + "\n");
	}
	result.append("---------------------------------------------------------------------\n");
	return result;
}

String ProblemInstance::showCompat() {
	String result;
	result = "-------------------Nodo1, Nodo2, Compatibilidad----------------------\n";
	for(int r = 0; r < this->nodeCompat_->getRows(); ++r) {
		for(int c = 0; c < this->nodeCompat_->getCols(); ++c) {
			result.append(this->getNode(r) + "," + this->getNode(c) + ", " + convertToString(this->getCompat(r, c)) + "\n");
		}
	}
	result.append("---------------------------------------------------------------------\n");
	return result;
}

String ProblemInstance::showCover() {
	String result;
	result = "---------------------Node, {Cubrimiento}:----------------------------\n";
	bool withComma;
	for (Int2ObjectOpenHashMap::iterator it=this->nodeCover_->begin();it!=this->nodeCover_->end();++it) {
		result.append(this->getNode(it->first)+", {");
		withComma = false;
		for(IntSet::iterator it1=it->second->begin();it1!=it->second->end();++it1) {
			if (!withComma) {
				result.append(this->getNode(*it1));
				withComma = true;
			}
			else {
				result.append("," + this->getNode(*it1));
			}
		}
		result.append("}\n");
	}
	result.append("---------------------------------------------------------------------\n");
	return result;
}
