/*
 * restrictedHACSolver.h
 *
 *  Created on: 13/08/2013
 *      Author: zero
 */

#ifndef RESTRICTEDHACSOLVER_H_
#define RESTRICTEDHACSOLVER_H_

#include "multiplicativeEffortProduceAndChooseSolver.h"

class RestrictedHACSolver: public MultiplicativeEffortProduceAndChooseSolver {
public:
	RestrictedHACSolver(ProblemInstance* problem) :  MultiplicativeEffortProduceAndChooseSolver(problem) {

	}
	virtual ~RestrictedHACSolver();

    SnowFlakeVector* produceManySnowflakesSingleCluster(int numToProduce);
    SnowFlakeVector* produceManySnowflakes(int numToProduce);
protected:
	bool tryMerge(MapIntIntSet* clustering);
    void singleLinkClustering(MapIntIntSet* clustering);
private:
    struct compareTupleIntDouble {
        compareTupleIntDouble(TupleIntDouble aTuple, TupleIntDouble anotherTuple) :
            aTuple_(aTuple), anotherTuple_(anotherTuple) {}
        TupleIntDouble aTuple_;
        TupleIntDouble anotherTuple_;

        /*inline bool operator() (int node1, int node2) {
            return problem_.getCompat(pivot_, node2) >  problem_.getCompat(pivot_, node1);
        }*/
    };
};

#endif /* RESTRICTEDHACSOLVER_H_ */
