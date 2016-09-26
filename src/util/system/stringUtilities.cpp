/*
 * stringUtilities.cpp
 *
 *  Created on: 25/08/2013
 *      Author: zero
 */

#include "stringUtilities.h"
#include <sstream>
#include <boost/lexical_cast.hpp>


void stringToVectorSplit(std::string aLine, std::string aSeparator, std::vector<std::string>& outVector)
{
	std::string::size_type pos;
	std::string element;
	pos=aLine.find(aSeparator);
	element = aLine.substr(0,pos);
	outVector.push_back(element);

	while(pos!=std::string::npos) {
		aLine=aLine.substr(pos+1,aLine.size());
		pos=aLine.find(aSeparator);
		element = aLine.substr(0,pos);
		outVector.push_back(element);
	}
}

void trim(std::string& str)
{
	std::string trim_chars = "\t ";
	std::string::size_type pos = str.find_last_not_of(trim_chars);

	if(pos != std::string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(trim_chars);

		if(pos != std::string::npos) {
			str.erase(0, pos);
		}
	}

	else {
		str.erase(str.begin(), str.end());
	}
}

std::string convertToString(int aNumber)
{
	std::string s;
	std::stringstream out;
	out << aNumber;
	return out.str();
}

std::string convertToString(double aNumber)
{
	std::string s;
	std::stringstream out;
	out << aNumber;
	return out.str();
}

int convertToInt(const std::string& aNumber)
{
	return boost::lexical_cast<int>(aNumber);
}

double convertToDouble(const std::string& aNumber)
{
	return boost::lexical_cast<double>(aNumber);
}

/*void removeString(std::string& str, const std::string& strToRemove) {
    std::string::size_type pos = str.find_last_not_of(strToRemove);
    str.find_first_not_of(strToRemove);



    if(pos != std::string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(strToRemove);
        if(pos != std::string::npos) {
            str.erase(0, pos);
        }
    }
    else {
        str.erase(str.begin(), str.end());
    }
}*/
