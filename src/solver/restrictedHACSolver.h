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
    double sim(IntSet* snowflake1, IntSet* snowflake2);
    struct compareTupleIntDouble {
        bool operator() (const TupleIntDouble& aTuple, const TupleIntDouble& anotherTuple) const {
            return std::get<1>(aTuple) < std::get<1>(anotherTuple);
        }
    };
    typedef priority_queue<TupleIntDouble, VectorTupleIntDouble, compareTupleIntDouble> PrtyQueueTupleIntDouble;
    typedef std::vector<PrtyQueueTupleIntDouble*> VectorPrtyQueueTupleIntDouble;
};

#endif /* RESTRICTEDHACSOLVER_H_ */
