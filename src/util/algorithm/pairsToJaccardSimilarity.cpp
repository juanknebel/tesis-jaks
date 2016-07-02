/*
 * pairsToJaccardSimilarity.cpp
 *
 *  Created on: 15/08/2013
 *      Author: zero
 */

#include "pairsToJaccardSimilarity.h"
#include "../system/stringUtilities.h"

String PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR = "\t";

void PairsToJaccardSimilarity::execute(String fileParams)
{
	//Hacer un parse del archivo de configuracion
	String fileInput = "";
	String fileOutput = "";
	bool intersection = false;
	int keyField = 0;
	PairsToJaccardSimilarity::execute(fileInput, fileOutput, intersection, keyField);
}

void PairsToJaccardSimilarity::execute(String fileNameInput, String fileNameOutput, bool intersection, int keyField)
{
	PairsToJaccardSimilarity pairs(fileNameInput,fileNameOutput, intersection, keyField);
	MapStringStringSet sets;
	FileInput inFile;
	inFile.open(fileNameInput.c_str());
	FileOutput outFile;
	outFile.open(fileNameOutput.c_str());
	String line;

	while(getline(inFile, line, '\n')) {
		trim(line);
		StrVector tokens;
		stringToVectorSplit(line,PairsToJaccardSimilarity::DEFAULT_FIELD_SEPARATOR,tokens);
		String key = tokens[pairs.keyField_];
		String value = tokens[pairs.valueField_];

		if(sets.count(key) == 0) {
			StringSet *aSet = new StringSet;
			aSet->insert(value);
			sets[key] = *aSet;
		}

		else {
			StringSet& mappedSet = sets[key];
			mappedSet.insert(value);
		}
	}

	for (MapStringStringSet::iterator it = sets.begin(); it != sets.end(); ++it) {
		String k1 = it->first;
		StringSet& s1 = it->second;

		for (MapStringStringSet::iterator it2 = it; it2 != sets.end(); ++it2) {
			if (it2 == it) {
				continue;
			}

			String k2 = it2->first;
			StringSet& s2 = it2->second;
			Double value = (pairs.intersection_ == true) ? pairs.computeIntersection(s1, s2) : pairs.computeJaccard(s1, s2);

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

PairsToJaccardSimilarity::PairsToJaccardSimilarity(String fileNameInput, String fileNameOutput, bool intersection, int keyField)
{
	this->init(fileNameInput,fileNameOutput, intersection, keyField);
}

PairsToJaccardSimilarity::~PairsToJaccardSimilarity()
{

}

void PairsToJaccardSimilarity::init(String fileNameInput, String fileNameOutput, bool intersection, int keyField)
{
	this->fileNameInput_ = fileNameInput;
	this->fileNameOutput_ = fileNameOutput;
	this->intersection_ = intersection;
	this->keyField_ = keyField;
	this->valueField_ = this->keyField_ == 0 ? 1 : 0;
}

Double PairsToJaccardSimilarity::computeIntersection(StringSet& set1, StringSet& set2)
{
	StringSet* smallerSet = (set1.size() > set2.size()) ? &set2 : &set1;
	StringSet* largerSet = (set1.size() > set2.size()) ? &set1 : &set2;
	Uint intersection = 0;

	for (StringSet::iterator it = smallerSet->begin(); it != smallerSet->end(); ++it) {
		if (largerSet->count(*it) > 0) {
			++intersection;
		}
	}

	return (Double) intersection;
}

Double PairsToJaccardSimilarity::computeJaccard(StringSet& set1, StringSet& set2)
{
	StringSet* smallerSet = (set1.size() > set2.size()) ? &set2 : &set1;
	StringSet* largerSet = (set1.size() > set2.size()) ? &set1 : &set2;
	Uint intersection = 0;
	StringSet unionSet;

	for (StringSet::iterator it = smallerSet->begin(); it != smallerSet->end(); ++it) {
		unionSet.insert(*it);

		if (largerSet->count(*it) > 0) {
			++intersection;
		}
	}

	if (intersection == 0) {
		return 0.0;
	}

	for (StringSet::iterator it = largerSet->begin(); it != largerSet->end(); ++it) {
		if (unionSet.count(*it) == 0) {
			unionSet.insert(*it);
		}
	}

	return ((Double) intersection / (Double) unionSet.size());
}
