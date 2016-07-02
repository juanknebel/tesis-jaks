#include "priorityQueue.h"
#include "../util/system/exception.h"

PriorityQueue::PriorityQueue()
{
	this->theQueue_ = new PrtyQueueTupleIntDouble();
	this->blackListElements_ = new std::map<int, bool>;
	this->nextKey = 0;
}

int PriorityQueue::push(TupleIntDouble element)
{
	int key = this->nextKey;
	this->theQueue_->push(KeyTupleIntDouble(key, element));
	(*this->blackListElements_)[key] = false;
	this->nextKey++;

	return key;

}

TupleIntDouble PriorityQueue::top()
{
	if (this->theQueue_->empty()) {
		throw Exception(__FILE__, __LINE__, "Can not get the top element of an empty stack");
	}

	else {
		KeyTupleIntDouble element = this->theQueue_->top();

		while (this->blackListElements_->find(std::get<0>(element)) != this->blackListElements_->end()
		        && (*this->blackListElements_)[std::get<0>(element)] == true) {
			this->theQueue_->pop();
			element = this->theQueue_->top();
		}

		return std::get<1>(element);
	}
}

void PriorityQueue::pop()
{
	KeyTupleIntDouble element = this->theQueue_->top();
	this->theQueue_->pop();
	(*this->blackListElements_)[std::get<0>(element)] = true;
}

void PriorityQueue::erase(int key)
{
	(*this->blackListElements_)[key] = true;
}

bool PriorityQueue::empty()
{
	return this->theQueue_->empty();
}

int PriorityQueue::size()
{
	return this->theQueue_->size();
}

PriorityQueue::~PriorityQueue()
{
	delete this->theQueue_;
	delete this->blackListElements_;
}
