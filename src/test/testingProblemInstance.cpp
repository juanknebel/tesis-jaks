/*
 * testingProblemInstance.cpp
 *
 *  Created on: 16/07/2013
 *      Author: jknebel
 */

#include <iostream>
#include "testingProblemInstance.h"

TestingProblemInstance::TestingProblemInstance()
{
	this->theProblem_ = 0;
}

TestingProblemInstance::TestingProblemInstance(const TestingProblemInstance& testingProblem)
{
	this->theProblem_ = testingProblem.theProblem_;
}

TestingProblemInstance::~TestingProblemInstance()
{
	delete this->theProblem_;
}

void TestingProblemInstance::setProblem(ProblemInstance *theProblem)
{
	this->theProblem_ = theProblem;
}

void TestingProblemInstance::testNumNodes(int numNodes)
{
	if (this->theProblem_->numNodes() == numNodes) {
		std::cout<<"Numero de nodos funciono"<<std::endl;
	}

	else {
		std::cout<<"Numero de nodos fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetCost(int id, double cost)
{
	if (this->theProblem_->getCost(id) == cost) {
		std::cout<<"Costo funciono"<<std::endl;
	}

	else {
		std::cout<<"Costo fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetBudget(double budget)
{
	if (this->theProblem_->getbudget() == budget) {
		std::cout<<"Presupuesto funciono"<<std::endl;
	}

	else {
		std::cout<<"Presupuesto fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetCompat(int id1, int id2, double value)
{
	if (this->theProblem_->getCompat(id1,id2) == value) {
		std::cout<<"Obtencion de un elemento funciono"<<std::endl;
	}

	else {
		std::cout<<"Obtencion de un elemento fallo"<<std::endl;
	}
}

void TestingProblemInstance::testNormalizeNodeCompat(ProblemInstance* problem)
{

}

void TestingProblemInstance::testGetNode(int id, std::string node)
{
	if (this->theProblem_->getNode(id) == node) {
		std::cout<<"Obtencion del nodo funciono"<<std::endl;
	}

	else {
		std::cout<<"Obtencion del nodo fallo"<<std::endl;
	}
}

void TestingProblemInstance::testGetId(std::string node, int id)
{
	if (this->theProblem_->getId(node) == id) {
		std::cout<<"Obtencion del id funciono"<<std::endl;
	}

	else {
		std::cout<<"Obtencion del id fallo"<<std::endl;
	}
}

void TestingProblemInstance::testMaxPairwiseCompatibility(std::set<int>* aSet, std::set<int>* otherSet, double result)
{
	if (this->theProblem_->maxPairwiseCompatibility(*aSet, *otherSet) == result) {
		std::cout<<"Mayor compatibilidad funciono"<<std::endl;
	}

	else {
		std::cout<<"Mayor compatibilidad fallo"<<std::endl;
	}
}

void TestingProblemInstance::testCreateIdNodeMappings(std::vector<std::string>* nodes, ProblemInstance* problem)
{
	bool notFail = true;

	for (std::vector<std::string>::iterator it = nodes->begin(); it != nodes->end(); ++it) {
		int id1 = this->theProblem_->getId(*it);
		int id2 = problem->getId(*it);
		std::string str1 = this->theProblem_->getNode(id1);
		std::string str2 = problem->getNode(id2);
		notFail = notFail && (id1 == id2) && (str1 == str2) && (str1 == *it);
	}

	if (notFail) { //BELLEEEEEEZAAAAAA NENEEEEEEEEEEEEE
		std::cout<<"El mapping funciono"<<std::endl;
	}

	else {
		std::cout<<"El mapping no fallo"<<std::endl;
	}
}
