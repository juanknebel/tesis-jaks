/*
 * problemInstance.h
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#ifndef PROBLEMINSTANCE_H_
#define PROBLEMINSTANCE_H_

#include "../matrix/matrixConcrete.h"
#include <set>
#include <fstream>

class ProblemInstance {
private:
	int specificItem_;

protected:
	/**
	 * The budget available.
	 */
    double budget_;
	/**
	 * Cost of adding a node to the solution.
	 */
    std::map<int, double> *nodeCost_;
	/**
	 * Attribute to be covered.
	 */
    std::map<int, std::set<int>*> *nodeCover_;
	/**
	 * Compatibility between two nodes.
	 */	
    MatrixWrapper *nodeCompat_;
    /**
     * Compatibility with specific profile
     */
    std::map<int, double> *nodeSpecificCompat_;
	/**
	 * Identifiers of nodes.
	 */
    std::map<std::string, int> *node2id_;
    std::map<int, std::string> *id2node_;
	/**
	 * Se mantiene un puntero al conjunto de claves de nodeCost para no tener que calcularlo cada vez que se necesita
	 */
    std::set<int> *ids_;
public:
	ProblemInstance();
    ProblemInstance(double budget);
	virtual ~ProblemInstance();

    virtual std::set<int>& getIds();
	virtual int numNodes();
    virtual double getCost(int id);
    double getbudget();
    virtual const std::set<int>* getCover(int id);
    virtual double getCompat(int id1, int id2);
    virtual double getCompatWithSpecificProfile(int id1, int id2);
    virtual MatrixWrapper* getCompat();
	virtual void normalizeNodeCompat();
    virtual std::string getNode(int id);
    int getId(std::string);
    double maxPairwiseCompatibility(const std::set<int>& aSet, const std::set<int>& otherSet);
    double maxPairwiseCompatibilityWithSpecificProfile(const std::set<int>& aSet, const std::set<int>& otherSet);
    //double maxPairwiseCompatibility(const SnowFlake& aSnow, const SnowFlake& otherSnow);
    void createIdNodeMappings(std::vector<std::string> nodes);

	void setSpecificItem(int specificItem);
	int getSpecificItem();
};

#endif /* PROBLEMINSTANCE_H_ */
