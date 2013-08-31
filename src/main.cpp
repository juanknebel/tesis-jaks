//============================================================================
// Name        : main.cpp
// Author      : jk, as
// Version     :
// Copyright   :
// Description :
//============================================================================

#include "test/testSuites.h"

int main(int argc, char *argv[]) {
	//testMatrix();
	//testProblemInstanceFromFiles("../files/");
	//testMetisWrapper();
	//testClustering();
	testClusterAndPickSolver("../files/");
	return 0;
}
