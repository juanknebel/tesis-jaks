/*
 * snowFlake.cpp
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#include "snowFlake.h"

double calculateCost(std::set<Flake>& elements) {
    double cost = 0.0;
    for (auto aFlake : elements) {
        cost += aFlake.getCost();
    }
    return cost;
}

int calculateCoverSize(std::set<Flake>& elements) {
    int coverSize = 0;
    for (auto aFlake : elements) {
        coverSize += aFlake.getCover().size();
    }
    return coverSize;
}

std::set<int> SnowFlake::getInternalIds() const {
    std::set<int> ids = std::set<int> ();
    for (auto aFlake : this->elements_) {
        ids.insert(aFlake.getId());
    }
    return ids;
}

SnowFlake::SnowFlake() {
    this->identificator_ = -1;
    this->elements_ = std::set<Flake> ();
    this->cost_ = -1.0;
    this->coverSize_ = -1;
}

SnowFlake::SnowFlake(const SnowFlake &snowflake) {
    this->identificator_ = snowflake.getIdentificator();
    this->elements_ = std::set<Flake> (snowflake.ids());
    this->cost_ = calculateCost(this->elements_);
    this->coverSize_ = calculateCoverSize(this->elements_);


}

SnowFlake::SnowFlake(const std::set<Flake> &elements) {
    this->identificator_ = -1;
    this->elements_ = std::set<Flake> (elements);
    this->cost_ = calculateCost(this->elements_);
    this->coverSize_ = calculateCoverSize(this->elements_);
}

SnowFlake &SnowFlake::operator=(const SnowFlake &snowflake) {
    this->identificator_ = snowflake.getIdentificator();
    this->elements_ = std::set<Flake> (snowflake.ids());
    this->cost_ = calculateCost(this->elements_);
    this->coverSize_ = calculateCoverSize(this->elements_);
    return *this;
}


SnowFlake::~SnowFlake() {
    this->identificator_ = -1;
    this->elements_.clear();
}

bool SnowFlake::operator<(const SnowFlake& snowflake) const {
    /*
     * TODO: arreglar esto!
     * return snowflake.getSumIntraCompat() < this->getSumIntraCompat();
     */
    return false;
}

std::ostream& operator<< (std::ostream& stream,const SnowFlake& snowFlake) {
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

const std::set<Flake>& SnowFlake::ids() const {
    return this->elements_;
}

int SnowFlake::getIdentificator() const {
    return this->identificator_;
}

void SnowFlake::setIdentificator(int theIdentificator) {
    this->identificator_ = theIdentificator;
}

double SnowFlake::getCost() const {
    return this->cost_;
}

int SnowFlake::getCoverSize() const {
    return this->coverSize_;
}

double SnowFlake::getSumIntraCompat(const SnowFlake& snowFlake, ProblemInstance& theProblem) {
    double sumCompat = 0.0;
    std::set<Flake> ids = snowFlake.ids();
    for (auto aFlakeIt = ids.begin(); aFlakeIt != ids.end(); ++aFlakeIt) {
        for (auto otherFlakeIt = ids.begin(); otherFlakeIt != ids.end(); ++otherFlakeIt) {
            sumCompat += Flake::getCompat(*aFlakeIt, *otherFlakeIt, theProblem);
        }
    }
    return sumCompat;
}

double SnowFlake::getSumIntraCompatWithSpecificProfile(const SnowFlake& snowFlake, ProblemInstance& theProblem) {
    double sumCompat = 0.0;
    std::set<Flake> ids = snowFlake.ids();
    for (auto aFlakeIt = ids.begin(); aFlakeIt != ids.end(); ++aFlakeIt) {
        for (auto otherFlakeIt = ids.begin(); otherFlakeIt != ids.end(); ++otherFlakeIt) {
            sumCompat += Flake::getCompat(*aFlakeIt, *otherFlakeIt, theProblem);
            //sum += this->problem_->getCompatWithSpecificProfile(*it, *it2);
        }
    }
    return sumCompat;
}

double SnowFlake::getMinCompat(const SnowFlake& snowFlake, ProblemInstance& theProblem) {
    double minCompat = std::numeric_limits<double>::max();
    std::set<Flake> ids = snowFlake.ids();
    for (auto aFlakeIt = ids.begin(); aFlakeIt != ids.end(); ++aFlakeIt) {
        for (auto otherFlakeIt = ids.begin(); otherFlakeIt != ids.end(); ++otherFlakeIt) {
            double compat = Flake::getCompat(*aFlakeIt, *otherFlakeIt, theProblem);
            if (compat > 0.0 && compat < minCompat) {
                minCompat = compat;
            }
        }
    }
    return minCompat;
}


double SnowFlake::objetiveFunction(const std::vector<SnowFlake>& solution, double gamma, ProblemInstance& theProblem) {
    double sumIntraCompat = SnowFlake::getIntra(solution, theProblem);
    double sumOneMinusInter = SnowFlake::getInter(solution, theProblem);
    return ((1.0 - gamma) * sumIntraCompat) + (gamma * sumOneMinusInter);
}

double SnowFlake::getInter(const std::vector<SnowFlake> &solution, ProblemInstance& theProblem) {
    double sumIntraCompat = 0.0;
    for (auto aSnowFlake : solution) {
        sumIntraCompat += (aSnowFlake.ids().size() > 0) ? SnowFlake::getSumIntraCompat(aSnowFlake, theProblem) : 0;
    }
    return sumIntraCompat;
}

double SnowFlake::getIntra(const std::vector<SnowFlake> &solution, ProblemInstance& theProblem) {
    double sumOneMinusInter = 0.00;
    for (auto aSnowFlakeIt = solution.begin(); aSnowFlakeIt != solution.end(); ++aSnowFlakeIt) {
        if (aSnowFlakeIt->ids().size() > 0) {
            for (auto otherSnowFlakeIt = aSnowFlakeIt; otherSnowFlakeIt != solution.end(); ++otherSnowFlakeIt) {
                if (otherSnowFlakeIt->ids().size() > 0) {
                    sumOneMinusInter += 1.0 - SnowFlake::maxPairwiseCompatibility(*aSnowFlakeIt, *otherSnowFlakeIt, theProblem);
                }
            }
        }
    }
    return sumOneMinusInter;
}

double SnowFlake::maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake, ProblemInstance& theProblem) {
    return theProblem.maxPairwiseCompatibility(aSnowFlake.getInternalIds(), otherSnowFlake.getInternalIds());
}

void SnowFlake::sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector, ProblemInstance& theProblem) {
    /*
     * TODO: arreglar esto
     */
    //std::sort(snowFlakesVector.begin(), snowFlakesVector.end());
}
