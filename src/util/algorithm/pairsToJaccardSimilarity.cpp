/*
 * pairsToJaccardSimilarity.cpp
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#include "pairsToJaccardSimilarity.h"
#include "../system/stringUtilities.h"

std::string PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR = "\t";

void PairsToJaccardSimilarity::execute(std::string fileParams)
{
	//Hacer un parse del archivo de configuracion
	std::string fileInput = "";
	std::string fileOutput = "";
	bool intersection = false;
	int keyField = 0;
	PairsToJaccardSimilarity::execute(fileInput, fileOutput, intersection, keyField);
}

void PairsToJaccardSimilarity::execute(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField)
{
	PairsToJaccardSimilarity pairs(fileNameInput,fileNameOutput, intersection, keyField);
	std::map<std::string, std::set<std::string>> sets;
	std::ifstream inFile;
	inFile.open(fileNameInput.c_str());
	std::ofstream outFile;
	outFile.open(fileNameOutput.c_str());
	std::string line;

	while(getline(inFile, line, '\n')) {
		trim(line);
		std::vector<std::string> tokens;
		stringToVectorSplit(line,PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR,tokens);
		std::string key = tokens[pairs.keyField_];
		std::string value = tokens[pairs.valueField_];

		if(sets.count(key) == 0) {
			std::set<std::string> *aSet = new std::set<std::string>;
			aSet->insert(value);
			sets[key] = *aSet;
		}

		else {
			std::set<std::string>& mappedSet = sets[key];
			mappedSet.insert(value);
		}
	}

	for (std::map<std::string, std::set<std::string>>::iterator it = sets.begin(); it != sets.end(); ++it) {
		std::string k1 = it->first;
		std::set<std::string>& s1 = it->second;

		for (std::map<std::string, std::set<std::string>>::iterator it2 = it; it2 != sets.end(); ++it2) {
			if (it2 == it) {
				continue;
			}

			std::string k2 = it2->first;
			std::set<std::string>& s2 = it2->second;
			double value = (pairs.intersection_ == true) ? pairs.computeIntersection(s1, s2) : pairs.computeJaccard(s1, s2);

			if (value > 0.0) {
				outFile <<k1<<PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR<<k2<<PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR<<value<<"\n";
			}
		}
	}

	inFile.close();
	outFile.close();
}

PairsToJaccardSimilarity::PairsToJaccardSimilarity()
{
	this->init("","",false,0);
}

PairsToJaccardSimilarity::PairsToJaccardSimilarity(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField)
{
	this->init(fileNameInput,fileNameOutput, intersection, keyField);
}

PairsToJaccardSimilarity::~PairsToJaccardSimilarity()
{

}

void PairsToJaccardSimilarity::init(std::string fileNameInput, std::string fileNameOutput, bool intersection, int keyField)
{
	this->fileNameInput_ = fileNameInput;
	this->fileNameOutput_ = fileNameOutput;
	this->intersection_ = intersection;
	this->keyField_ = keyField;
	this->valueField_ = this->keyField_ == 0 ? 1 : 0;
}

double PairsToJaccardSimilarity::computeIntersection(std::set<std::string>& set1, std::set<std::string>& set2)
{
	std::set<std::string>* smallerSet = (set1.size() > set2.size()) ? &set2 : &set1;
	std::set<std::string>* largerSet = (set1.size() > set2.size()) ? &set1 : &set2;
	int intersection = 0;

	for (std::set<std::string>::iterator it = smallerSet->begin(); it != smallerSet->end(); ++it) {
		if (largerSet->count(*it) > 0) {
			++intersection;
		}
	}

	return (double) intersection;
}

double PairsToJaccardSimilarity::computeJaccard(std::set<std::string>& set1, std::set<std::string>& set2)
{
	std::set<std::string>* smallerSet = (set1.size() > set2.size()) ? &set2 : &set1;
	std::set<std::string>* largerSet = (set1.size() > set2.size()) ? &set1 : &set2;
	int intersection = 0;
	std::set<std::string> unionSet;

	for (std::set<std::string>::iterator it = smallerSet->begin(); it != smallerSet->end(); ++it) {
		unionSet.insert(*it);

		if (largerSet->count(*it) > 0) {
			++intersection;
		}
	}

	if (intersection == 0) {
		return 0.0;
	}

	for (std::set<std::string>::iterator it = largerSet->begin(); it != largerSet->end(); ++it) {
		if (unionSet.count(*it) == 0) {
			unionSet.insert(*it);
		}
	}

	return ((double) intersection / (double) unionSet.size());
}
