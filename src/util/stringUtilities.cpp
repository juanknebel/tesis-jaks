/*
 * stringUtilities.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include "stringUtilities.h"
#include <sstream>

void stringToVectorSplit(String aLine, String aSeparator, StrVector& outVector) {
	String::size_type pos;
	String element;
	pos=aLine.find(aSeparator);
	element = aLine.substr(0,pos);
	outVector.push_back(element);
	while(pos!=String::npos) {
		aLine=aLine.substr(pos+1,aLine.size());
		pos=aLine.find(aSeparator);
		element = aLine.substr(0,pos);
		outVector.push_back(element);
	}
}

void trim(String& str) {
	String trim_chars = "\t ";
	String::size_type pos = str.find_last_not_of(trim_chars);
	if(pos != String::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(trim_chars);
		if(pos != String::npos) {
			str.erase(0, pos);
		}
	}
	else {
		str.erase(str.begin(), str.end());
	}
}

String convertToString(int aNumber) {
	String s;
	std::stringstream out;
	out << aNumber;
	return out.str();
}


