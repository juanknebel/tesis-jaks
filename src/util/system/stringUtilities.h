/*
 * stringUtilities.h
 *
 *  Created on: 20/08/2013
 *      Author: jknebel
 */

#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <vector>

void stringToVectorSplit(std::string aLine, std::string aSeparator, std::vector<std::string>& outVector);

void trim(std::string& str);

std::string convertToString(int aNumber);

std::string convertToString(double aNumber);

int convertToInt(const std::string& aNumber);

double convertToDouble(const std::string& aNumber);


#endif /* STRINGUTILITIES_H_ */
