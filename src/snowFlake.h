/*
 * snowFlake.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef SNOWFLAKE_H_
#define SNOWFLAKE_H_

#include "util/id2Str.h"
#include "problemInstance.h"

class SnowFlake {
private:
	IntSet *elements_;
	ProblemInstance *problem_;

	Double getMinCompat();

public:
	SnowFlake();
	SnowFlake(const SnowFlake&);
	SnowFlake(const IntSet& elements, ProblemInstance* problem);
	~SnowFlake();
	bool operator<(const SnowFlake& snowFlake) const;

	Double getCost();
	int getCoverSize();
	String toString(const Id2Str* node2name);
	Double getSumIntraCompat() const;
	static void sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector);
	IntSet& ids();
	static String showSolution(std::vector<SnowFlake>& solutions);
};

#endif /* SNOWFLAKE_H_ */
