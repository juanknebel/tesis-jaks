#ifndef PRIORITYQQUEUE_H
#define PRIORITYQQUEUE_H

#include <queue>
#include <map>
#include <tuple>

class PriorityQueue {
private:
    struct compareTupleIntDouble {
        bool operator() (const std::tuple<int,std::tuple<int, double>>& aTuple, const std::tuple<int,std::tuple<int, double>>& anotherTuple) const {
            std::tuple<int, double> tuple1 = std::get<1>(aTuple);
            std::tuple<int, double> tuple2 = std::get<1>(anotherTuple);

            return std::get<1>(tuple1) < std::get<1>(tuple2);
        }
    };
    typedef std::priority_queue<std::tuple<int,std::tuple<int, double>>, std::vector<std::tuple<int,std::tuple<int, double>>>, compareTupleIntDouble> PrtyQueueTupleIntDouble;

    PrtyQueueTupleIntDouble *theQueue_;
    std::map<int, bool> *blackListElements_;
    int nextKey;
public:
    PriorityQueue();
    int push(std::tuple<int, double> element);
    std::tuple<int, double> top();
    void pop();
    void erase(int key);
    bool empty();
    int size();
    ~PriorityQueue();
};

#endif // PRIORITYQQUEUE_H
