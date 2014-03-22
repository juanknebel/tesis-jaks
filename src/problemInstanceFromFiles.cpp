/*
 * problemInstanceFromFiles.cpp
 *
 *  Created on: 24/07/2013
 *      Author: jknebel
 */

#include <stdlib.h>
#include "problemInstanceFromFiles.h"
#include "util/stringUtilities.h"

ProblemInstanceFromFiles::ProblemInstanceFromFiles() : ProblemInstance() {

}

ProblemInstanceFromFiles::ProblemInstanceFromFiles(String fileCosts, String fileCompat, String fileCover, Double budget) : ProblemInstance(budget) {
	init(fileCosts, fileCompat, fileCover);
}

ProblemInstanceFromFiles::~ProblemInstanceFromFiles() {
}

void ProblemInstanceFromFiles::init(String fileCosts, String fileCompat, String fileCover) {
	this->loadIdMapping(fileCosts);
	this->loadInt2Double(fileCosts);
	this->loadAndSymmetrizeMatrix(this->numNodes(), fileCompat);
	this->loadInt2IntSet(fileCover);
}

void ProblemInstanceFromFiles::loadIdMapping(String fileName) {
	//falta chequear si hay algun id duplicado!!!
	FileInput file;
	file.open(fileName.c_str());
	String theId;
	StrVector vectorOfIds;
	while(getline(file, theId, '\t')) {
		vectorOfIds.push_back(theId);
		getline(file, theId, '\n');
	}
	file.close();
	this->createIdNodeMappings(vectorOfIds);
}

void ProblemInstanceFromFiles::loadInt2Double(String fileName) {
	FileInput file;
	file.open(fileName.c_str());
	String line;
	int nodeId;
	while(getline(file, line, '\n')) {
		StrVector tokens;
		stringToVectorSplit(line,"\t",tokens);
		nodeId = this->getId(tokens[0]);
		if (nodeId >= 0) { // Skip silently nodes not mentioned in the cost file
			(*(*this).nodeCost_)[nodeId] = atof(tokens[1].c_str());
		}
	}
	file.close();
	for (MapIntDouble::iterator it = this->nodeCost_->begin(); it != this->nodeCost_->end(); ++it) {
		this->ids_->insert(it->first);
	}
}

void ProblemInstanceFromFiles::loadAndSymmetrizeMatrix(int nElements,  String fileName) {
	this->nodeCompat_ = new SparseDoubleMatrix2DImplementation(this->numNodes(), this->numNodes());
	FileInput file;
	file.open(fileName.c_str());
	String line;
	int nodeId1, nodeId2;
	while (getline(file, line, '\n')) {
		StrVector tokens;
		stringToVectorSplit(line, "\t", tokens);
		if (tokens.size() == 3) {
			nodeId1 = this->getId(tokens[0]);
			nodeId2 = this->getId(tokens[1]);
			if (nodeId1 >= 0 && nodeId2 >= 0) { // Skip silently nodes not mentioned in the cost fileCompat
				this->nodeCompat_->set(nodeId1, nodeId2, atof(tokens[2].c_str()));
				
			}
		}
	}
	file.close();
}

void ProblemInstanceFromFiles::loadInt2IntSet(String fileName) {
	FileInput file;
	file.open(fileName.c_str());
	String line;
	int nodeId;
	while (getline(file, line, '\n')) {
		StrVector tokens;
		stringToVectorSplit(line, "\t", tokens);
		nodeId = this->getId(tokens[0]);
		if (nodeId >=0) { // Skip silently nodes not mentioned in the cost file
			IntSet *aSet = new IntSet();
			for(int i = 1; i < tokens.size(); ++i) {
				aSet->insert(atoi(tokens[i].c_str()));
			}
			(*(*this).nodeCover_)[nodeId] = aSet;
		}
	}
	file.close();
}
