/*
 * problemInstanceFromFiles.cpp
 *
 *  Created on: 24/07/2013
 *      Author: jknebel
 */

#include "problemInstanceFromFiles.h"
#include "../util/system/stringUtilities.h"

ProblemInstanceFromFiles::ProblemInstanceFromFiles() : ProblemInstance() {

}

ProblemInstanceFromFiles::ProblemInstanceFromFiles(std::string fileCosts, std::string fileCompat, std::string fileCover, double budget) : ProblemInstance(budget) {
	init(fileCosts, fileCompat, fileCover);
}

ProblemInstanceFromFiles::~ProblemInstanceFromFiles() {
}

void ProblemInstanceFromFiles::init(std::string fileCosts, std::string fileCompat, std::string fileCover) {
	this->loadIdMapping(fileCosts);
	this->loadInt2Double(fileCosts);
	this->loadAndSymmetrizeMatrix(this->numNodes(), fileCompat);
    this->loadInt2IntSet(fileCover);
}

void ProblemInstanceFromFiles::loadIdMapping(std::string fileName) {
	//falta chequear si hay algun id duplicado!!!
	std::ifstream file;
	file.open(fileName.c_str());
    std::string theId;
	std::vector<std::string> vectorOfIds;
	while(getline(file, theId, '\t')) {
		vectorOfIds.push_back(theId);
		getline(file, theId, '\n');
	}
	file.close();
	this->createIdNodeMappings(vectorOfIds);
}

void ProblemInstanceFromFiles::loadInt2Double(std::string fileName) {
	std::ifstream file;
	file.open(fileName.c_str());
    std::string line;
	int nodeId;
	while(getline(file, line, '\n')) {
		std::vector<std::string> tokens;
		stringToVectorSplit(line,"\t",tokens);
		nodeId = this->getId(tokens[0]);
		if (nodeId >= 0) { // Skip silently nodes not mentioned in the cost file
			(*(*this).nodeCost_)[nodeId] = atof(tokens[1].c_str());
		}
	}
	file.close();
    for (std::map<int, double>::iterator it = this->nodeCost_->begin(); it != this->nodeCost_->end(); ++it) {
		this->ids_->insert(it->first);
	}
}

void ProblemInstanceFromFiles::loadAndSymmetrizeMatrix(int nElements,  std::string fileName) {
    this->nodeCompat_ = new MatrixConcrete(this->numNodes(), this->numNodes());
	std::ifstream file;
	file.open(fileName.c_str());
    std::string line;
	int nodeId1, nodeId2;
	while (getline(file, line, '\n')) {
		std::vector<std::string> tokens;
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

void ProblemInstanceFromFiles::loadInt2IntSet(std::string fileName) {
	std::ifstream file;
	file.open(fileName.c_str());
    std::string line;
	int nodeId;
	while (getline(file, line, '\n')) {
		std::vector<std::string> tokens;
		stringToVectorSplit(line, "\t", tokens);
		nodeId = this->getId(tokens[0]);
		if (nodeId >=0) { // Skip silently nodes not mentioned in the cost file
			std::set<int> *aSet = new std::set<int>();
			for(int i = 1; i < tokens.size(); ++i) {
				aSet->insert(atoi(tokens[i].c_str()));
			}
			(*(*this).nodeCover_)[nodeId] = aSet;
		}
	}
	file.close();
}
