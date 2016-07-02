/*
 * problemInstance.cpp
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#include "problemInstance.h"
#include "../util/system/stringUtilities.h"
#include <cassert>

ProblemInstance::ProblemInstance()
{
	this->budget_ = NAN;
	this->nodeCost_ = 0;
	this->nodeCover_ = 0;
	this->nodeCompat_ = 0;
	this->node2id_ = 0;
	this->id2node_ = 0;
	this->ids_ = 0;
	this->specificItem_ = -1;
}

ProblemInstance::ProblemInstance(Double budget)
{
	this->budget_ = budget;
	this->nodeCost_ = new MapIntDouble;
	this->nodeCover_ = new MapIntIntSet;
	this->nodeCompat_ = 0;
	this->node2id_ = new MapStringInt;
	this->id2node_ = new MapIntString;
	this->ids_ = new IntSet();
	this->specificItem_ = -1;
}

ProblemInstance::~ProblemInstance()
{
	delete this->nodeCost_;

	for (MapIntIntSet::iterator it = this->nodeCover_->begin(); it != this->nodeCover_->end(); ++it) {
		it->second->clear();
	}

	this->nodeCover_->clear();
	delete this->nodeCover_;
	delete this->nodeCompat_;
	this->ids_->clear();
	delete this->ids_;
}

IntSet& ProblemInstance::getIds()
{
	return *(this->ids_);
}

int ProblemInstance::numNodes()
{
	return this->nodeCost_->size();
}

Double ProblemInstance::getCost(int id)
{
	return this->nodeCost_->at(id);
}

Double ProblemInstance::getbudget()
{
	return this->budget_;
}

const IntSet* ProblemInstance::getCover(int id)
{
	return this->nodeCover_->at(id);
}

Double ProblemInstance::getCompat(int id1, int id2)
{
	assert (id1 < this->nodeCompat_->getRows());
	assert (id2 < this->nodeCompat_->getCols());

	if (id1 == id2) {
		return this->specificItem_ == id1 ? 0 : 1;
	}

	return this->nodeCompat_->get(id1, id2);
}

Double ProblemInstance::getCompatWithSpecificProfile(int id1, int id2)
{
	Double compatWithId1 = 0.0, compatWithId2 = 0.0;

	if (this->nodeSpecificCompat_->count(id1) > 0) {
		compatWithId1 = this->nodeSpecificCompat_->at(id1);
	}

	if (this->nodeSpecificCompat_->count(id2) > 0) {
		compatWithId2 = this->nodeSpecificCompat_->at(id2);
	}

	return this->getCompat(id1,id2) + compatWithId1 + compatWithId2;
}

SparseDoubleMatrix2D* ProblemInstance::getCompat()
{
	return this->nodeCompat_;
}

void ProblemInstance::normalizeNodeCompat()
{
	Double maxValue = this->nodeCompat_->getMaxValue();
	this->nodeCompat_->scalarMultiply(1.0/maxValue);
}

String ProblemInstance::getNode(int id)
{
	return this->id2node_->at(id);
}

int ProblemInstance::getId(String node)
{
	return this->node2id_->at(node);
}

Double ProblemInstance::maxPairwiseCompatibility(const IntSet& aSet, const IntSet& otherSet)
{
	Double maxCompatibility = 0.0;

	for (IntSet::iterator it1 = aSet.begin(); it1 != aSet.end(); ++it1) {
		for (IntSet::iterator it2 = otherSet.begin(); it2 != otherSet.end(); ++it2) {
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

Double ProblemInstance::maxPairwiseCompatibilityWithSpecificProfile(const IntSet& aSet, const IntSet& otherSet)
{
	Double maxCompatibility = 0.0;

	for (IntSet::iterator it1 = aSet.begin(); it1 != aSet.end(); ++it1) {
		for (IntSet::iterator it2 = otherSet.begin(); it2 != otherSet.end(); ++it2) {
			int n1 = (int) *it1;
			int n2 = (int) *it2;
			Double compatValue = this->getCompatWithSpecificProfile(n1, n2);

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

void ProblemInstance::createIdNodeMappings(StrVector nodes)
{
	int nextId = 0;

	for (StrVector::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		String nodeId(*it);
		(*(*this).node2id_)[nodeId]=nextId;
		(*(*this).id2node_)[nextId]=nodeId;
		++nextId;
	}
}

void ProblemInstance::setSpecificItem(int specificItem)
{
	this->specificItem_ = specificItem;
}

int ProblemInstance::getSpecificItem()
{
	return this->specificItem_;
}
