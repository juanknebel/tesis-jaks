/*
 * snowFlake.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef SNOWFLAKE_H_
#define SNOWFLAKE_H_

#include "../util/identificator/id2Str.h"
#include "problemInstance.h"

class SnowFlake {
private:
	/**
	 * The elements this snowflake is composed of.
	 */
	std::set<int> *elements_;
	/**
	 * The problem instance for which this snowflake was generated.
	 */
	ProblemInstance *problem_;

    double getMinCompat();

    unsigned int identificator_;

public:
	SnowFlake();
	SnowFlake(const SnowFlake& snowflake);
	SnowFlake(const std::set<int>& elements, ProblemInstance* problem);
	SnowFlake& operator=(const SnowFlake& snowflake);
	~SnowFlake();
	bool operator<(const SnowFlake& snowflake) const;

    double getCost();
	int getCoverSize();
    std::string toString(const Id2Str* node2name);
    double getSumIntraCompat() const;
	static void sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector);
	std::set<int>& ids() const;
    std::string getProblemNode(int aNode) const;
    static double objetiveFunction(const std::vector<SnowFlake>& solution, double interSimilarityWeight);
    unsigned int getIdentificator() const;
    void setIdentificator(unsigned int theIdentificator);
    static double maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake);
    double getSumIntraCompatWithSpecificProfile() const;
};

#endif /* SNOWFLAKE_H_ */
