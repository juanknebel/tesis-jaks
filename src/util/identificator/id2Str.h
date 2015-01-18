/*
 * id2Str.h
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#ifndef ID2STR_H_
#define ID2STR_H_

#include <fstream>
#include "identificationGeneretor.h"

class Id2Str {
private:
    std::map<std::string, std::string> *node2name_;
	Dao* dao_;

public:
	Id2Str();
    Id2Str(std::string fileName);
    Id2Str(IdentificationGeneretor* theIdentificator);
	~Id2Str();

    std::string getNodebyName(std::string node) const;
};


#endif /* ID2STR_H_ */
