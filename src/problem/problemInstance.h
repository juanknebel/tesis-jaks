/*
 * problemInstance.h
 *
 *  Created on: 09/07/2013
 *      Author: zero
 */

#ifndef PROBLEMINSTANCE_H_
#define PROBLEMINSTANCE_H_

#include "../matrix/matrixConcrete.h"
#include "../util/redefinitions.h"

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
	MapIntDouble *nodeCost_;
	/**
	 * Attribute to be covered.
	 */
	MapIntIntSet *nodeCover_;
	/**
	 * Compatibility between two nodes.
	 */
	SparseDoubleMatrix2D *nodeCompat_;
	/**
	 * Compatibility with specific profile
	 */
	MapIntDouble *nodeSpecificCompat_;
	/**
	 * Identifiers of nodes.
	 */
	MapStringInt *node2id_;
	MapIntString *id2node_;
	/**
	 * Se mantiene un puntero al conjunto de claves de nodeCost para no tener que calcularlo cada vez que se necesita
	 */
	IntSet *ids_;
public:
	ProblemInstance();
	ProblemInstance(Double budget);
	virtual ~ProblemInstance();

	virtual IntSet& getIds();
	virtual int numNodes();
	virtual Double getCost(int id);
	Double getbudget();
	virtual const IntSet* getCover(int id);
	virtual Double getCompat(int id1, int id2);
	virtual Double getCompatWithSpecificProfile(int id1, int id2);
	virtual SparseDoubleMatrix2D* getCompat();
	virtual void normalizeNodeCompat();
	virtual String getNode(int id);
	int getId(String);
	Double maxPairwiseCompatibility(const IntSet& aSet, const IntSet& otherSet);
	Double maxPairwiseCompatibilityWithSpecificProfile(const IntSet& aSet, const IntSet& otherSet);
	//Double maxPairwiseCompatibility(const SnowFlake& aSnow, const SnowFlake& otherSnow);
	void createIdNodeMappings(StrVector nodes);

	void setSpecificItem(int specificItem);
	int getSpecificItem();
};

#endif /* PROBLEMINSTANCE_H_ */
