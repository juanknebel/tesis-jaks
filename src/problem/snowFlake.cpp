/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"
#include "../util/system/stringUtilities.h"
#include <float.h>
#include "../util/logger/logger.h"

Double SnowFlake::getMinCompat() {
	Double minCompat = FLT_MAX;
	for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		for (IntSet::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
			Double compat = this->problem_->getCompat(*it, *it2);
			if (compat > 0.0 && compat < minCompat) {
				minCompat = compat;
			}
		}
	}
	return minCompat;
}

SnowFlake::SnowFlake() {
    this->elements_ = IntSet();
	this->problem_ = nullptr;
    this->identificator_ = 0;
}

SnowFlake::SnowFlake(const IntSet& elements, ProblemInstance* problem) {
	this->problem_ = problem;
	this->elements_ = IntSet(elements);
    this->identificator_ = 0;
}

SnowFlake::SnowFlake(const SnowFlake& snowflake){
	this->problem_ = snowflake.problem_;
	this->elements_ = IntSet(snowflake.elements_);
    this->identificator_ = snowflake.getIdentificator();
}

SnowFlake& SnowFlake::operator=(const SnowFlake& snowflake) {
	this->problem_ = snowflake.problem_;
    this->elements_.clear();
	this->elements_ = IntSet(snowflake.elements_);
    this->identificator_ = snowflake.getIdentificator();
	return *this;
}

SnowFlake::~SnowFlake() {
	this->elements_.clear();
	this->problem_ = nullptr;
}

bool SnowFlake::operator<(const SnowFlake& snowflake) const {
	return snowflake.getSumIntraCompat() < this->getSumIntraCompat();
}

Double SnowFlake::getCost() {
	Double sumCosts = 0.00;
	for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		sumCosts += this->problem_->getCost(*it);
	}
	return sumCosts;
}

int SnowFlake::getCoverSize() {
	IntSet covered;
	for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		const IntSet *aSetToInsert = this->problem_->getCover(*it);
		covered.insert(aSetToInsert->begin(), aSetToInsert->end());
	}

	return covered.size();
}

String SnowFlake::toString(const Id2Str* node2name) {
	String result = "";
	for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		Double cost;
		String node;
		cost = this->problem_->getCost(*it);
		node = this->problem_->getNode(*it);
		result.append(" * " + node + (node2name == NULL ? "" : " " + node2name->getNodebyName(node)));
		result.append(" (cost=" + convertToString(cost) + ")\n");
	}
	
	result.append("SIZE             = " + convertToString((int)this->elements_.size()) + "\n");
	result.append("COVERAGE         = " + convertToString(this->getCoverSize()) + "\n");
	result.append("COST             = " + convertToString(this->getCost()) + "\n");
	result.append("MIN_INTRA_COMPAT = " + convertToString(this->getMinCompat()) + "\n");
	result.append("SUM_INTRA_COMPAT = " + convertToString(this->getSumIntraCompat()) + "\n\n");
	return result;
}

Double SnowFlake::getSumIntraCompat() const {
	Double sum = 0.0;
	for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
		for (IntSet::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
			if (*it<*it2) {
				sum += this->problem_->getCompat(*it, *it2);
			}
		}
	}
	return sum;
}

Double SnowFlake::getSumIntraCompatWithSpecificProfile() const {
    Double sum = 0.0;
    for (IntSet::iterator it = this->elements_.begin(); it != this->elements_.end(); ++it) {
        for (IntSet::iterator it2 = this->elements_.begin(); it2 != this->elements_.end(); ++it2) {
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

IntSet& SnowFlake::ids() const {
	return const_cast<IntSet&> (this->elements_);
}

String SnowFlake::getProblemNode(int aNode) const {
    return this->problem_->getNode(aNode);
}

Double SnowFlake::objetiveFunction(const std::vector<SnowFlake>& solution, Double interSimilarityWeight) {
  Double sumIntraCompat = 0.00;
  Double sumOneMinusInter = 0.00;
  for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
    if (it->ids().size() > 0) {
      sumIntraCompat += it->getSumIntraCompat();
    }
  }
  for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
    if (it->ids().size() > 0) {
      for (std::vector<SnowFlake>::const_iterator it2 = it; it2 != solution.end(); ++it2) {
        if (it2->ids().size() > 0) {
          double temp = 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
          int id1 = it->getIdentificator();
          int id2 = it2->getIdentificator();
          sumOneMinusInter += 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
        }
      }
    }
  }
  return ((1.0 - interSimilarityWeight) * sumIntraCompat) + (interSimilarityWeight * sumOneMinusInter);
}

Double SnowFlake::getIntra(const std::vector<SnowFlake>& solution, Double interSimilarityWeight) {
  Double sumIntraCompat = 0.00;
  for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
    if (it->ids().size() > 0) {
      sumIntraCompat += it->getSumIntraCompat();
    }
  }
  return sumIntraCompat;
}

Double SnowFlake::getInter(const std::vector<SnowFlake>& solution, Double interSimilarityWeight) {
  Double sumOneMinusInter = 0.00;
  for (std::vector<SnowFlake>::const_iterator it = solution.begin(); it != solution.end(); ++it) {
    if (it->ids().size() > 0) {
      for (std::vector<SnowFlake>::const_iterator it2 = it; it2 != solution.end(); ++it2) {
        if (it2->ids().size() > 0) {
          double temp = 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
          int id1 = it->getIdentificator();
          int id2 = it2->getIdentificator();
          sumOneMinusInter += 1.0 - it->problem_->maxPairwiseCompatibility(it->ids(), it2->ids());
        }
      }
    }
  }
  return sumOneMinusInter;
}

Uint SnowFlake::getIdentificator() const {
    return this->identificator_;
}

void SnowFlake::setIdentificator(Uint theIdentificator) {
    this->identificator_ = theIdentificator;
}

Double SnowFlake::maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake) {
    return aSnowFlake.problem_->maxPairwiseCompatibility(aSnowFlake.ids(), otherSnowFlake.ids());
}
