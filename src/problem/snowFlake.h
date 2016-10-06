/*
 * snowFlake.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef SNOWFLAKE_H_
#define SNOWFLAKE_H_

#include <set>
#include "flake.h"
#include <vector>

class SnowFlake {
private:
	std::set<Flake> elements_;
	int identificator_;
    double cost_;
    int coverSize_;
    std::set<int> getInternalIds() const;

public:
	SnowFlake();
	SnowFlake(const SnowFlake& snowflake);
	SnowFlake(const std::set<Flake>& elements);
	SnowFlake& operator=(const SnowFlake& snowflake);
	~SnowFlake();
	bool operator<(const SnowFlake& snowflake) const;
	friend std::ostream& operator<< (std::ostream& stream,const SnowFlake& snowFlake);
	const std::set<Flake>& ids() const;
    int getIdentificator() const;
    void setIdentificator(int theIdentificator);
    double getCost() const;
    int getCoverSize() const;


	static double getSumIntraCompat(const SnowFlake& snowFlake, ProblemInstance& theProblem);
    static double getSumIntraCompatWithSpecificProfile(const SnowFlake& snowFlake, ProblemInstance& theProblem);
    static double getMinCompat(const SnowFlake& snowFlake, ProblemInstance& theProblem);

    static double objetiveFunction(const std::vector<SnowFlake>& solution, double gamma, ProblemInstance& theProblem);
	static double getInter(const std::vector<SnowFlake> &solution, ProblemInstance& theProblem);
	static double getIntra(const std::vector<SnowFlake> &solution, ProblemInstance& theProblem);
    static double maxPairwiseCompatibility(const SnowFlake& aSnowFlake, const SnowFlake& otherSnowFlake, ProblemInstance& theProblem);
	static void sortByDecresingSumCompat(std::vector<SnowFlake>& snowFlakesVector, ProblemInstance& theProblem);

};

#endif /* SNOWFLAKE_H_ */
