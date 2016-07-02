#ifndef PRIORITYQQUEUE_H
#define PRIORITYQQUEUE_H
#include "../util/redefinitions.h"
#include <queue>

class PriorityQueue {
private:
	struct compareTupleIntDouble {
		bool operator() (const KeyTupleIntDouble& aTuple, const KeyTupleIntDouble& anotherTuple) const {
			TupleIntDouble tuple1 = std::get<1>(aTuple);
			TupleIntDouble tuple2 = std::get<1>(anotherTuple);

			return std::get<1>(tuple1) < std::get<1>(tuple2);
		}
	};
	typedef std::priority_queue<KeyTupleIntDouble, KeyVectorTupleIntDouble, compareTupleIntDouble> PrtyQueueTupleIntDouble;

	PrtyQueueTupleIntDouble *theQueue_;
	std::map<int, bool> *blackListElements_;
	int nextKey;
public:
	PriorityQueue();
	int push(TupleIntDouble element);
	TupleIntDouble top();
	void pop();
	void erase(int key);
	bool empty();
	int size();
	~PriorityQueue();
};

#endif // PRIORITYQQUEUE_H
