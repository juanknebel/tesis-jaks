/*
 * testingProblemInstanceFromFiles.cpp
 *
 *  Created on: 25/07/2013
 *      Author: zero
 */

#include "testingProblemInstanceFromFiles.h"

TestingProblemInstanceFromFiles::TestingProblemInstanceFromFiles(std::string directory)
{
	this->init(directory);
	this->theProblem_ = new ProblemInstanceFromFiles(this->fileNodeCost_, this->fileNodeCompatibility_, this->fileNodeCover_, 1000.00);
}

TestingProblemInstanceFromFiles::TestingProblemInstanceFromFiles(const TestingProblemInstanceFromFiles& testingProblem)
{
	this->directory_ = testingProblem.directory_;
	this->fileNodeCompatibility_ = testingProblem.fileNodeCompatibility_;
	this->fileNodeCost_ = testingProblem.fileNodeCost_;
	this->fileNodeCover_ = testingProblem.fileNodeCover_;
	this->fileNodeName_ = testingProblem.fileNodeName_;
	this->fileTypeName_ = testingProblem.fileTypeName_;
	this->theProblem_ = testingProblem.theProblem_;
}

TestingProblemInstanceFromFiles::~TestingProblemInstanceFromFiles()
{
	delete this->theProblem_;
}

void TestingProblemInstanceFromFiles::init(std::string directory)
{
	this->directory_ = directory;
	this->fileNodeCompatibility_ = this->directory_ + "node_compatibility.csv";
	this->fileNodeCost_ = this->directory_ + "node_cost.csv";
	this->fileNodeCover_ = this->directory_ + "node_cover.csv";
	this->fileNodeName_ = this->directory_ + "node_name.csv";
	this->fileTypeName_ = this->directory_ + "type_name.csv";
	this->theProblem_ = 0;
}
