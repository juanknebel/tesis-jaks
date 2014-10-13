/*
 * testSuites.h
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#ifndef TESTSUITES_H_
#define TESTSUITES_H_

#include <string>
#include "../util/system/Logger.h"
#include "../solver/restrictedHACWithSpecificItemSolver.h"

void initDefaultDebug();

void testOverLoadFunction();

void testDB();

void testMatrix();

void testProblemInstance();

void testProblemInstanceFromFiles(std::string);

void testMetisWrapper();

void testClustering();

void testClusterAndPickSolver(std::string);

void testConfiguration(int argc, char *argv[]);

void testRestrictedHACWithSpecificItemSolver();
#endif /* TESTSUITES_H_ */
