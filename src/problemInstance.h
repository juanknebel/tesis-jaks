/*
 * problemInstance.h
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#ifndef PROBLEMINSTANCE_H_
#define PROBLEMINSTANCE_H_

#include "matrixConcrete.h"
#include "util/redefinitions.h"

typedef MatrixWrapper SparseDoubleMatrix2D;
typedef MatrixConcrete SparseDoubleMatrix2DImplementation;

class ProblemInstance {
private:
	int specificItem_;

protected:
	/**
	 * The budget available.
	 */
	Double budget_;
	/**
	 * Cost of adding a node to the solution.
	 */
	Int2DoubleOpenHashMap *nodeCost_;
	/**
	 * Attribute to be covered.
	 */
	Int2ObjectOpenHashMap *nodeCover_;
	/**
	 * Compatibility between two nodes.
	 */	
	SparseDoubleMatrix2D *nodeCompat_;
	/**
	 * Identifiers of nodes.
	 */
	Object2IntOpenHashMap *node2id_;
	Int2ObjectOpenHashMapString *id2node_;
	/**
	 * Se mantiene un puntero al conjunto de claves de nodeCost para no tener que calcularlo cada vez que se
	 */
	IntSet *ids_; necesita
	String showBudget();
	String showCosts();
	String showCompat();
	String showCover();

public:
	ProblemInstance();
	ProblemInstance(Double budget);
	~ProblemInstance();

	IntSet& getIds();
	int numNodes();
	Double getCost(int id);
	Double getbudget();
	const IntSet* getCover(int id);
	Double getCompat(int id1, int id2);
	SparseDoubleMatrix2D* getCompat();
	void normalizeNodeCompat();
	String getNode(int id);
	int getId(String);
	Double maxPairwiseCompatibility(const IntSet& aSet, const IntSet& otherSet);
	//Double maxPairwiseCompatibility(const SnowFlake& aSnow, const SnowFlake& otherSnow);
	void createIdNodeMappings(StrVector nodes);
	String showMe();

	void setSpecificItem(int specificItem);
	int getSpecificItem();
};

#endif /* PROBLEMINSTANCE_H_ */
