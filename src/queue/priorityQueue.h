#ifndef PRIORITYQQUEUE_H
#define PRIORITYQQUEUE_H
#include "../util/redefinitions.h"
#include <queue>

class PriorityQueue {
private:
    struct compareTupleIntDouble {
        bool operator() (const TupleIntDouble& aTuple, const TupleIntDouble& anotherTuple) const {
            return std::get<1>(aTuple) < std::get<1>(anotherTuple);
        }
    };
    typedef std::priority_queue<TupleIntDouble, VectorTupleIntDouble, compareTupleIntDouble> PrtyQueueTupleIntDouble;

    PrtyQueueTupleIntDouble *theQueue_;
    std::map<int, bool> *blackListElements_;
public:
    PriorityQueue();
    void push(TupleIntDouble element);
    TupleIntDouble top();
    void pop();
    void erase(int element);
    bool empty();
    int size();
    ~PriorityQueue();
};

#endif // PRIORITYQQUEUE_H
