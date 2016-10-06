#include "priorityQueue.h"
#include "../util/system/exception.h"

PriorityQueue::PriorityQueue()
{
	this->theQueue_ = new PrtyQueueTupleIntDouble();
	this->blackListElements_ = new std::map<int, bool>;
	this->nextKey = 0;
}

int PriorityQueue::push(std::pair<int, double> element)
{
	int key = this->nextKey;
	this->theQueue_->push(std::pair<int,std::pair<int, double>>(key, element));
	(*this->blackListElements_)[key] = false;
	this->nextKey++;

	return key;

}

std::pair<int, double> PriorityQueue::top()
{
	if (this->theQueue_->empty()) {
		throw Exception(__FILE__, __LINE__, "Can not get the top element of an empty stack");
	}

	else {
		std::pair<int,std::pair<int, double>> element = this->theQueue_->top();

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
	std::pair<int,std::pair<int, double>> element = this->theQueue_->top();
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

PriorityQueue::PriorityQueue(const PriorityQueue &otherQue) {
	this->theQueue_ = new PrtyQueueTupleIntDouble(*otherQue.theQueue_);
	this->blackListElements_ = new std::map<int, bool>(*otherQue.blackListElements_);
	this->nextKey = otherQue.nextKey;
}

PriorityQueue &PriorityQueue::operator=(const PriorityQueue &otherQue) {
	this->theQueue_ = new PrtyQueueTupleIntDouble(*otherQue.theQueue_);
	this->blackListElements_ = new std::map<int, bool>(*otherQue.blackListElements_);
	this->nextKey = otherQue.nextKey;
	return *this;
}
