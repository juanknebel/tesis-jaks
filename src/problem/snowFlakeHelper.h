//
// Created by zero on 19/04/15.
//

#ifndef TESIS_JAKS_EXE_SNOWFLAKEHELPER_H
#define TESIS_JAKS_EXE_SNOWFLAKEHELPER_H

#include "problemInstance.h"
#include "snowFlake.h"
#include "../util/identificator/id2Str.h"


class SnowFlakeHelper {
public:
    SnowFlakeHelper() {}
    ~SnowFlakeHelper() {}

    double getMinCompat(SnowFlake& snowflake, ProblemInstance& problem);
    double getCost(SnowFlake& snowflake, ProblemInstance& problem);
    int getCoverSize(SnowFlake &snowflake, ProblemInstance &problem);
    double getSumIntraCompat(SnowFlake &snowflake, ProblemInstance &problem);
    double getSumIntraCompatWithSpecificProfile(SnowFlake &snowflake, ProblemInstance &problem);
    double maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake,
                                    ProblemInstance &problem);
    double objetiveFunction(const std::vector<SnowFlake>& solution, double interSimilarityWeight,
                            ProblemInstance &problem);
    std::string getProblemNode(int node, ProblemInstance &problem);
    std::string toString(SnowFlake& snowFlake, ProblemInstance &problem, const Id2Str* node2name);
};


#endif //TESIS_JAKS_EXE_SNOWFLAKEHELPER_H
