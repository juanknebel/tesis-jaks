/*
 * testingProblemInstance.h
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#ifndef TESTINGPROBLEMINSTANCE_H_
#define TESTINGPROBLEMINSTANCE_H_

#include "../problemInstance.h"

class TestingProblemInstance {
private:
	ProblemInstance *theProblem_;

public:
	TestingProblemInstance();
	TestingProblemInstance(const TestingProblemInstance& );
	~TestingProblemInstance();

	void setProblem(ProblemInstance *theProblem);
	void testNumNodes(int numNodes);
	void testGetCost(int id, Double cost);
	void testGetBudget(Double budget);
	void testGetCompat(int id1, int id2, Double value);
	void testNormalizeNodeCompat(ProblemInstance* problem);
	void testGetNode(int id, String node);
	void testGetId(String node, int id);
	void testMaxPairwiseCompatibility(IntSet* aSet, IntSet* otherSet, Double result);
	void testCreateIdNodeMappings(StrVector* nodes, ProblemInstance* problem);
};


#endif /* TESTINGPROBLEMINSTANCE_H_ */
