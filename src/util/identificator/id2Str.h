/*
 * id2Str.h
 *
 *  Created on: 30/07/2013
 *      Author: zero
 */

#ifndef ID2STR_H_
#define ID2STR_H_
#include <map>
#include <string>
#include "../../problem/element.h"
#include "../../dao/dao.h"
#include <memory>


class Id2Str {
private:
	std::unique_ptr<std::map<std::string, std::string>> node2name_;

public:
	Id2Str();
	Id2Str(const Element* element, Dao* dao);
	~Id2Str();

	std::string getNodebyName(std::string node) const;
};


#endif /* ID2STR_H_ */
