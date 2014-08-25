/*
 * id2Str.h
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#ifndef ID2STR_H_
#define ID2STR_H_

#include "redefinitions.h"
#include "identificationGeneretor.h"

class Id2Str {
private:
	MapStringString *node2name_;
	Dao* dao_;

public:
	Id2Str();
	Id2Str(String fileName);
    Id2Str(IdentificationGeneretor* theIdentificator);
	~Id2Str();

	String getNodebyName(String node) const;
};


#endif /* ID2STR_H_ */
