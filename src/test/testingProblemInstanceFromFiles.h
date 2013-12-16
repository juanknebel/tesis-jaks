/*
 * testingProblemInstanceFromFiles.h
 *
 *  Created on: 25/07/2013
 *      Author: zero
 */

#ifndef TESTINGPROBLEMINSTANCEFROMFILES_H_
#define TESTINGPROBLEMINSTANCEFROMFILES_H_

#include "../problemInstanceFromFiles.h"

class TestingProblemInstanceFromFiles {
private:
	ProblemInstanceFromFiles *theProblem_;
	String directory_;
	String fileNodeCompatibility_;
	String fileNodeCost_;
	String fileNodeCover_;
	String fileNodeName_;
	String fileTypeName_;

	void init(String directory);
public:
	TestingProblemInstanceFromFiles(String directory="/home/$USER/");
	TestingProblemInstanceFromFiles(const TestingProblemInstanceFromFiles& );
	~TestingProblemInstanceFromFiles();
};

#endif /* TESTINGPROBLEMINSTANCEFROMFILES_H_ */
