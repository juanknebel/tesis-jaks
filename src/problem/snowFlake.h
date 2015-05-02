/*
 * snowFlake.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef SNOWFLAKE_H_
#define SNOWFLAKE_H_

#include "problemInstance.h"

class SnowFlake {
private:
	/**
	 * The elements this snowflake is composed of.
	 */
	std::unique_ptr<std::set<int>> elements_;
	/**
	 * The identification of the snowflake
	 */
    int identificator_;

public:
	SnowFlake();
	SnowFlake(const SnowFlake& snowflake);
	SnowFlake(std::unique_ptr<std::set<int>> elements);
	SnowFlake& operator=(const SnowFlake& snowflake);
	~SnowFlake() {}

	static void sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector, ProblemInstance& problem);
	std::set<int>& ids() const;
    unsigned int getIdentificator() const;
    void setIdentificator(unsigned int theIdentificator);
};

#endif /* SNOWFLAKE_H_ */
