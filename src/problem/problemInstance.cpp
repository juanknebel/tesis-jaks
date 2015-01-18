/*
 * problemInstance.cpp
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#include "problemInstance.h"
#include "../util/system/stringUtilities.h"
#include <cassert>

ProblemInstance::ProblemInstance() {
	this->budget_ = NAN;
	this->nodeCost_ = 0;
	this->nodeCover_ = 0;
	this->nodeCompat_ = 0;
	this->node2id_ = 0;
	this->id2node_ = 0;
	this->ids_ = 0;
	this->specificItem_ = -1;
}

ProblemInstance::ProblemInstance(double budget) {
	this->budget_ = budget;
    this->nodeCost_ = new std::map<int, double>;
	this->nodeCover_ = new std::map<int, std::set<int>*>;
	this->nodeCompat_ = 0;
    this->node2id_ = new std::map<std::string, int>;
    this->id2node_ = new std::map<int, std::string>;
	this->ids_ = new std::set<int>();
	this->specificItem_ = -1;
}

ProblemInstance::~ProblemInstance() {
	delete this->nodeCost_;
	for (std::map<int, std::set<int>*>::iterator it = this->nodeCover_->begin(); it != this->nodeCover_->end(); ++it) {
		it->second->clear();
	}
	this->nodeCover_->clear();
	delete this->nodeCover_;
	delete this->nodeCompat_;
	this->ids_->clear();
	delete this->ids_;
}

std::set<int>& ProblemInstance::getIds() {
	return *(this->ids_);
}

int ProblemInstance::numNodes() {
	return this->nodeCost_->size();
}

double ProblemInstance::getCost(int id) {
	return this->nodeCost_->at(id);
}

double ProblemInstance::getbudget() {
	return this->budget_;
}

const std::set<int>* ProblemInstance::getCover(int id) {
	return this->nodeCover_->at(id);
}

double ProblemInstance::getCompat(int id1, int id2) {
	assert (id1 < this->nodeCompat_->getRows());
	assert (id2 < this->nodeCompat_->getCols());
	if (id1 == id2) {
		return this->specificItem_ == id1 ? 0 : 1;
	}
	return this->nodeCompat_->get(id1, id2);
}

double ProblemInstance::getCompatWithSpecificProfile(int id1, int id2) {
    double compatWithId1 = 0.0, compatWithId2 = 0.0;
    if (this->nodeSpecificCompat_->count(id1) > 0) {
        compatWithId1 = this->nodeSpecificCompat_->at(id1);
    }
    if (this->nodeSpecificCompat_->count(id2) > 0) {
        compatWithId2 = this->nodeSpecificCompat_->at(id2);
    }
    return this->getCompat(id1,id2) + compatWithId1 + compatWithId2;
}

MatrixWrapper* ProblemInstance::getCompat() {
	return this->nodeCompat_;
}

void ProblemInstance::normalizeNodeCompat() {
	double maxValue = this->nodeCompat_->getMaxValue();
	this->nodeCompat_->scalarMultiply(1.0/maxValue);
}

std::string ProblemInstance::getNode(int id) {
	return this->id2node_->at(id);
}

int ProblemInstance::getId(std::string node) {
	return this->node2id_->at(node);
}

double ProblemInstance::maxPairwiseCompatibility(const std::set<int>& aSet, const std::set<int>& otherSet) {
	double maxCompatibility = 0.0;
	for (std::set<int>::iterator it1 = aSet.begin(); it1 != aSet.end(); ++it1) {
		for (std::set<int>::iterator it2 = otherSet.begin(); it2 != otherSet.end(); ++it2){
			int n1 = (int) *it1;
			int n2 = (int) *it2;
			double compatValue = this->getCompat(n1, n2);
			if (compatValue > maxCompatibility) {
				maxCompatibility = compatValue;
			}
		}
	}
	return maxCompatibility;
}

double ProblemInstance::maxPairwiseCompatibilityWithSpecificProfile(const std::set<int>& aSet, const std::set<int>& otherSet) {
    double maxCompatibility = 0.0;
    for (std::set<int>::iterator it1 = aSet.begin(); it1 != aSet.end(); ++it1) {
        for (std::set<int>::iterator it2 = otherSet.begin(); it2 != otherSet.end(); ++it2){
            int n1 = (int) *it1;
            int n2 = (int) *it2;
            double compatValue = this->getCompatWithSpecificProfile(n1, n2);
            if (compatValue > maxCompatibility) {
                maxCompatibility = compatValue;
            }
        }
    }
    return maxCompatibility;
}

/*double ProblemInstance::maxPairwiseCompatibility(const SnowFlake& aSnow, const SnowFlake& otherSnow) {
	return this->maxPairwiseCompatibility(aSnow.ids(), otherSnow.ids());
}*/

void ProblemInstance::createIdNodeMappings(std::vector<std::string> nodes) {
	int nextId = 0;
	for (std::vector<std::string>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        std::string nodeId(*it);
		(*(*this).node2id_)[nodeId]=nextId;
		(*(*this).id2node_)[nextId]=nodeId;
		++nextId;
	}
}

void ProblemInstance::setSpecificItem(int specificItem){
	this->specificItem_ = specificItem;
}

int ProblemInstance::getSpecificItem(){
	return this->specificItem_;
}
