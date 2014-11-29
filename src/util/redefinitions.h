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
#include <iostream>
#include <tuple>
#include "system/Logger.h"

typedef double Double;
typedef unsigned int Uint;
typedef std::tuple<int, Double> TupleIntDouble;
typedef std::tuple<Double, bool> TupleDoubleBool;
typedef std::string String;
typedef std::set<int> IntSet;
typedef std::set<String> StringSet;
typedef std::map<int, Double> MapIntDouble;
typedef std::map<int, String> MapIntString;
typedef std::map<String, int> MapStringInt;
typedef std::map<String, String> MapStringString;
typedef std::map<int, IntSet*> MapIntIntSet;
typedef std::map<String, StringSet> MapStringStringSet;
typedef std::vector<TupleIntDouble> TupleIntDoubleVector;
typedef std::vector<String> StrVector;
typedef std::vector<Double> DblVector;
typedef std::vector<int> IntVector;
typedef std::vector<bool> BoolVector;
typedef std::ifstream FileInput;
typedef std::ofstream FileOutput;
typedef std::vector<TupleIntDouble> VectorTupleIntDouble;

#endif /* REDEFINITIONS_H_ */
