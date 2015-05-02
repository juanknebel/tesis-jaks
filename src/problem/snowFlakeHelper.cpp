//
// Created by zero on 19/04/15.
//

#include <float.h>
#include "snowFlakeHelper.h"
#include "../util/system/stringUtilities.h"

double SnowFlakeHelper::getMinCompat(SnowFlake& snowflake, ProblemInstance& problem) {
    double minCompat = FLT_MAX;
    for (auto elem1 : snowflake.ids()) {
        for (auto elem2 : snowflake.ids()) {
            double compat = problem.getCompat(elem1, elem2);
            if (compat > 0.0 && compat < minCompat) {
                minCompat = compat;
            }
        }
    }
    return minCompat;
}

double SnowFlakeHelper::getCost(SnowFlake &snowflake, ProblemInstance &problem) {
    double sumCosts = 0.00;
    for (auto elem : snowflake.ids()) {
        sumCosts += problem.getCost(elem);
    }
    return sumCosts;
}

int SnowFlakeHelper::getCoverSize(SnowFlake &snowflake, ProblemInstance &problem) {
    std::set<int> covered;
    for (auto elem : snowflake.ids()) {
        const std::set<int> *aSetToInsert = problem.getCover(elem);
        covered.insert(aSetToInsert->begin(), aSetToInsert->end());
    }

    return const_cast<int> (covered.size());
}

double SnowFlakeHelper::getSumIntraCompat(SnowFlake &snowflake, ProblemInstance &problem) {
    double sum = 0.0;
    for (auto elem : snowflake.ids()) {
        for (auto elem1 : snowflake.ids()) {
            if (elem < elem1) {
                sum += problem.getCompat(elem, elem1);
            }
        }
    }
    return sum;
}

double SnowFlakeHelper::getSumIntraCompatWithSpecificProfile(SnowFlake &snowflake, ProblemInstance &problem) {
    double sum = 0.0;
    for (auto elem : snowflake.ids()) {
        for (auto elem1 : snowflake.ids()) {
            if (elem < elem1) {
                sum += problem.getCompatWithSpecificProfile(elem, elem1);
            }
        }
    }
    return sum;
}

double SnowFlakeHelper::maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake,
                                           ProblemInstance &problem) {
    return problem.maxPairwiseCompatibility(aSnowFlake.ids(), otherSnowFlake.ids());
}

double SnowFlakeHelper::objetiveFunction(const std::vector<SnowFlake>& solution, double interSimilarityWeight,
                                         ProblemInstance &problem) {
    double sumIntraCompat = 0.00;
    double sumOneMinusInter = 0.00;
    for (auto elem : solution) {
        sumIntraCompat += this->getSumIntraCompat(elem, problem);
    }

    for (auto elem : solution) {
        for (auto elem1 : solution) {
            sumOneMinusInter += 1.0 - this->maxPairwiseCompatibility(elem, elem1, problem);
        }
    }
    sumOneMinusInter = sumOneMinusInter / 2.0;
    return ((1.0 - interSimilarityWeight) * sumIntraCompat) + (interSimilarityWeight * sumOneMinusInter);
}

std::string SnowFlakeHelper::getProblemNode(int node, ProblemInstance &problem) {
    return problem.getNode(node);
}

std::string SnowFlakeHelper::toString(SnowFlake& aSnowFlake, ProblemInstance &problem, Id2Str const *node2name) {
    std::string result = "";
    std::set<int> theIds = aSnowFlake.ids();
    for (auto elem : theIds) {
        double cost;
        std::string node;
        cost = problem.getCost(elem);
        node = problem.getNode(elem);
        result.append(" * " + node + (node2name == NULL ? "" : " " + node2name->getNodebyName(node)));
        result.append(" (cost=" + convertToString(cost) + ")\n");
    }

    result.append("SIZE             = " + convertToString((int)theIds.size()) + "\n");
    result.append("COVERAGE         = " + convertToString(this->getCoverSize(aSnowFlake, problem)) + "\n");
    result.append("COST             = " + convertToString(this->getCost(aSnowFlake, problem)) + "\n");
    result.append("MIN_INTRA_COMPAT = " + convertToString(this->getMinCompat(aSnowFlake, problem)) + "\n");
    result.append("SUM_INTRA_COMPAT = " + convertToString(this->getSumIntraCompat(aSnowFlake, problem)) + "\n\n");
    return result;
}
