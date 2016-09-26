/*
 * testingProblemInstanceFromFiles.h
 *
 *  Created on: 25/07/2013
 *      Author: zero
 */

#ifndef TESTINGPROBLEMINSTANCEFROMFILES_H_
#define TESTINGPROBLEMINSTANCEFROMFILES_H_

#include "../problem/problemInstanceFromFiles.h"

class TestingProblemInstanceFromFiles {
private:
	ProblemInstanceFromFiles *theProblem_;
	std::string directory_;
	std::string fileNodeCompatibility_;
	std::string fileNodeCost_;
	std::string fileNodeCover_;
	std::string fileNodeName_;
	std::string fileTypeName_;

	void init(std::string directory);
public:
	TestingProblemInstanceFromFiles(std::string directory="/home/$USER/");
	TestingProblemInstanceFromFiles(const TestingProblemInstanceFromFiles& );
	~TestingProblemInstanceFromFiles();
};

#endif /* TESTINGPROBLEMINSTANCEFROMFILES_H_ */
