/*
 * testingProblemInstance.h
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#ifndef TESTINGPROBLEMINSTANCE_H_
#define TESTINGPROBLEMINSTANCE_H_

#include "../problem/problemInstance.h"

class TestingProblemInstance {
private:
	ProblemInstance *theProblem_;

public:
	TestingProblemInstance();
	TestingProblemInstance(const TestingProblemInstance& );
	~TestingProblemInstance();

	void setProblem(ProblemInstance *theProblem);
	void testNumNodes(int numNodes);
	void testGetCost(int id, double cost);
	void testGetBudget(double budget);
	void testGetCompat(int id1, int id2, double value);
	void testNormalizeNodeCompat(ProblemInstance* problem);
	void testGetNode(int id, std::string node);
	void testGetId(std::string node, int id);
	void testMaxPairwiseCompatibility(std::set<int>* aSet, std::set<int>* otherSet, double result);
	void testCreateIdNodeMappings(std::vector<std::string>* nodes, ProblemInstance* problem);
};


#endif /* TESTINGPROBLEMINSTANCE_H_ */
