/*
 * snowFlake.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef SNOWFLAKE_H_
#define SNOWFLAKE_H_

//#include "../util/identificator/id2Str.h"
#include "problemInstance.h"

class SnowFlake {
private:
	/**
	 * The elements this snowflake is composed of.
	 */
	IntSet elements_;
	/**
	 * The problem instance for which this snowflake was generated.
	 */
	ProblemInstance *problem_;

	Uint identificator_;

public:
	SnowFlake();
	SnowFlake(const SnowFlake& snowflake);
	SnowFlake(const IntSet& elements, ProblemInstance* problem);
	SnowFlake& operator=(const SnowFlake& snowflake);
	~SnowFlake();
	bool operator<(const SnowFlake& snowflake) const;

	Double getCost() const;
	double getCostNode(int aNode) const;
	int getCoverSize() const;
	Double getSumIntraCompat() const;
	static void sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector);
	IntSet& ids() const;
	String getProblemNode(int aNode) const;
	static Double objetiveFunction(const std::vector<SnowFlake>& solution, Double interSimilarityWeight);
	Uint getIdentificator() const;
	void setIdentificator(Uint theIdentificator);
	static Double maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake);
	static Double getInter(const std::vector<SnowFlake>& solution, Double interSimilarityWeight);
	static Double getIntra(const std::vector<SnowFlake>& solution, Double interSimilarityWeight);
	Double getSumIntraCompatWithSpecificProfile() const;
	friend std::ostream& operator<< (std::ostream& stream,const SnowFlake& snowFlake);
	Double getMinCompat() const;
};

#endif /* SNOWFLAKE_H_ */
