/*
 * problemInstanceFromFiles.cpp
 *
 *  Created on: 24/07/2013
 *      Author: jknebel
 */

#include <stdlib.h>
#include <iostream>
#include "problemInstanceFromFiles.h"

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
	String theId, value;
	int nodeId;
	while(getline(file, theId, '\t')) {
		//TODO: reemplazar por el nuevo split para los strings
		getline(file, value, '\n');
		nodeId = this->getId(theId);
		(*(*this).nodeCost_)[nodeId] = atof(value.c_str());
	}
	file.close();
}

void ProblemInstanceFromFiles::loadAndSymmetrizeMatrix(int nElements,  String fileName) {
	this->nodeCompat_ = new SparseDoubleMatrix2DImplementation(this->numNodes(), this->numNodes());
	FileInput file;
	file.open(fileName.c_str());
	String theId, value;
	int nodeId1, nodeId2;
	while(getline(file, theId, '\t')) {
		//TODO: reemplazar por el nuevo split para los strings
		nodeId1 =this->getId(theId);
		getline(file, theId, '\t');
		nodeId2 =this->getId(theId);
		getline(file, value, '\n');
		this->nodeCompat_->set(nodeId1, nodeId2, atof(value.c_str()));
	}
	file.close();
}

void ProblemInstanceFromFiles::loadInt2IntSet(String fileName) {
	FileInput file;
	file.open(fileName.c_str());
	String line;
	int nodeId;
	unsigned long pos;
	while(getline(file, line, '\n')) {
		//TODO: reemplazar por el nuevo split para los strings
		pos=line.find('\t');
		IntSet *aSet = new IntSet();
		nodeId = this->getId(line.substr(0,pos));
		while(pos!=String::npos) {
			line=line.substr(pos+1,line.size());
			pos=line.find('\t');
			aSet->insert(atoi((line.substr(0,pos)).c_str()));
		}
		(*(*this).nodeCover_)[nodeId] = *aSet;
	}
	file.close();
}

void ProblemInstanceFromFiles::showMe() {
	this->showBudget();
	this->showCosts();
	this->showCompat();
	this->showCover();
}

void ProblemInstanceFromFiles::showBudget() {
	std::cout << "----------------------El presupuesto---------------------------------" << std::endl;
	std::cout << this->budget_ << std::endl;
	std::cout << "---------------------------------------------------------------------" << std::endl;
}

void ProblemInstanceFromFiles::showCosts() {
	std::cout << "-----------------------Nodo, Costo-----------------------------------" << std::endl;
	for(Int2DoubleOpenHashMap::iterator it = this->nodeCost_->begin(); it != this->nodeCost_->end(); ++it) {
		std::cout << this->getNode(it->first) << ", " << it->second << std::endl;
	}
	std::cout << "---------------------------------------------------------------------" << std::endl;
}

void ProblemInstanceFromFiles::showCompat() {
	std::cout << "-------------------Nodo1, Nodo2, Compatibilidad----------------------" << std::endl;
	for(int r = 1; r <= this->nodeCompat_->getRows(); ++r) {
		for(int c = 1; c <= this->nodeCompat_->getCols(); ++c) {
			std::cout << this->getNode(r) << "," << this->getNode(c) << ", " << this->getCompat(r, c) << std::endl;
		}
	}
	std::cout << "---------------------------------------------------------------------" << std::endl;
}

void ProblemInstanceFromFiles::showCover() {
	std::cout << "---------------------Node, {Cubrimiento}:----------------------------" << std::endl;
	bool withComma;
	for (Int2ObjectOpenHashMap::iterator it=this->nodeCover_->begin();it!=this->nodeCover_->end();++it) {
		std::cout << this->getNode(it->first)<<", {";
		withComma = false;
		for(IntSet::iterator it1=it->second.begin();it1!=it->second.end();++it1) {
			if (!withComma) {
				std::cout << this->getNode(*it1);
				withComma = true;
			}
			else {
				std::cout <<"," << this->getNode(*it1);
			}
		}
		std::cout << "}\n";
	}
	std::cout << "---------------------------------------------------------------------" << std::endl;
}
