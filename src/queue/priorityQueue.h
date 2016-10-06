#ifndef PRIORITYQQUEUE_H
#define PRIORITYQQUEUE_H
#include <queue>
#include <tuple>
#include <map>

class PriorityQueue {
private:
	struct compareTupleIntDouble {
		bool operator() (const std::pair<int,std::pair<int, double>>& aTuple, const std::pair<int,std::pair<int, double>>& anotherTuple) const {
			std::pair<int, double> tuple1 = std::get<1>(aTuple);
			std::pair<int, double> tuple2 = std::get<1>(anotherTuple);

			return std::get<1>(tuple1) < std::get<1>(tuple2);
		}
	};
	typedef std::priority_queue<std::pair<int,std::pair<int, double>>, std::vector<std::pair<int,std::pair<int, double>>>, compareTupleIntDouble> PrtyQueueTupleIntDouble;

	PrtyQueueTupleIntDouble *theQueue_;
	std::map<int, bool> *blackListElements_;
	int nextKey;
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue& otherQue);
	PriorityQueue& operator=(const PriorityQueue& otherQue);
	int push(std::pair<int, double> element);
	std::pair<int, double> top();
	void pop();
	void erase(int key);
	bool empty();
	int size();
	~PriorityQueue();
};

#endif // PRIORITYQQUEUE_H
