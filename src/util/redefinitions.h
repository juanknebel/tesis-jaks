/*
 * redefinitions.h
 *
 *  Created on: 15/07/2013
 *      Author: zero
 */

#ifndef REDEFINITIONS_H_
#define REDEFINITIONS_H_

#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>

typedef double Double;
typedef unsigned int Uint;
typedef std::string String;
typedef std::set<int> IntSet;
typedef std::set<String> StringSet;
typedef std::map<int, Double> Int2DoubleOpenHashMap;
typedef std::map<int, String> Int2ObjectOpenHashMapString;
typedef std::map<String, int> Object2IntOpenHashMap;
typedef std::map<String, String> Object2ObjectOpenHashMap;
typedef std::map<int, IntSet*> Int2ObjectOpenHashMap;
typedef std::map<String, StringSet> StringToStringSet;
typedef std::vector<String> StrVector;
typedef std::vector<Double> DblVector;
typedef std::vector<int> IntVector;
typedef std::ifstream FileInput;
typedef std::ofstream FileOutput;

#endif /* REDEFINITIONS_H_ */
