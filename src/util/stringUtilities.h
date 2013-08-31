/*
 * stringUtilities.h
 *
 *  Created on: 20/08/2013
 *      Author: jknebel
 */

#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include "redefinitions.h"


void stringToVectorSplit(String aLine, String aSeparator, StrVector& outVector);

void trim(String& str);

String convertToString(int aNumber);

String convertToString(Double aNumber);


#endif /* STRINGUTILITIES_H_ */
