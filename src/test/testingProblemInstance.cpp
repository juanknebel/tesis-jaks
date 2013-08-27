/*
 * testingProblemInstance.cpp
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#include <iostream>
#include "testingProblemInstance.h"

TestingProblemInstance::TestingProblemInstance() {
	this->theProblem_ = 0;
}

TestingProblemInstance::TestingProblemInstance(const TestingProblemInstance& testingProblem){
	this->theProblem_ = testingProblem.theProblem_;
}

TestingProblemInstance::~TestingProblemInstance() {
	delete this->theProblem_;
}

void TestingProblemInstance::setProblem(ProblemInstance *theProblem) {
	this->theProblem_ = theProblem;
}

void TestingProblemInstance::testNumNodes(int numNodes) {
	if (this->theProblem_->numNodes() == numNodes) {
		std::cout<<"Numero de nodos funciono"<<std::cout;
	}
	else {
		std::cout<<"Numero de nodos fallo"<<std::cout;
	}
}

void TestingProblemInstance::testGetCost(int id, Double cost) {
	if (this->theProblem_->getCost(id) == cost) {
		std::cout<<"Costo funciono"<<std::cout;
	}
	else {
		std::cout<<"Costo fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetBudget(Double budget) {
	if (this->theProblem_->getbudget() == budget) {
		std::cout<<"Presupuesto funciono"<<std::cout;
	}
	else {
		std::cout<<"Presupuesto fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetCompat(int id1, int id2, Double value) {
	if (this->theProblem_->getCompat(id1,id2) == value) {
		std::cout<<"Obtencion de un elemento funciono"<<std::endl;
	}
	else {
		std::cout<<"Obtencion de un elemento fallo"<<std::endl;
	}
}

void TestingProblemInstance::testNormalizeNodeCompat(ProblemInstance* problem) {

}

void TestingProblemInstance::testGetNode(int id, String node) {
	if (this->theProblem_->getNode(id) == node) {
		std::cout<<"Obtencion del nodo funciono"<<std::endl;
	}
	else {
		std::cout<<"Obtencion del nodo fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetId(String node, int id) {
	if (this->theProblem_->getId(node) == id) {
		std::cout<<"Obtencion del id funciono"<<std::endl;
	}
	else {
		std::cout<<"Obtencion del id fallo"<<std::endl;
	}
}

void TestingProblemInstance::testMaxPairwiseCompatibility(IntSet* aSet, IntSet* otherSet, Double result) {
	if (this->theProblem_->maxPairwiseCompatibility(*aSet, *otherSet) == result) {
		std::cout<<"Mayor compatibilidad funciono"<<std::endl;
	}
	else {
		std::cout<<"Mayor compatibilidad fallo"<<std::endl;
	}
}

void TestingProblemInstance::testCreateIdNodeMappings(StrVector* nodes, ProblemInstance* problem) {
	bool notFail = true;
	for (StrVector::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		int id1 = this->theProblem_->getId(*it);
		int id2 = problem->getId(*it);
		String str1 = this->theProblem_->getNode(id1);
		String str2 = problem->getNode(id2);
		notFail = notFail && (id1 == id2) && (str1 == str2) && (str1 == *it);
	}

	if (notFail) { //BELLEEEEEEZAAAAAA NENEEEEEEEEEEEEE
		std::cout<<"El mapping funciono"<<std::endl;
	}
	else {
		std::cout<<"El mapping no fallo"<<std::endl;
	}
}
