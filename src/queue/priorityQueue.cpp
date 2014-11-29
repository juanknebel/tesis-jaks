#include "priorityQueue.h"
#include "../util/system/exception.h"

PriorityQueue::PriorityQueue() {
    this->theQueue_ = new PrtyQueueTupleIntDouble();
    this->blackListElements_ = new std::map<int, bool>;
}

void PriorityQueue::push(TupleIntDouble element) {
    this->theQueue_->push(element);
    (*this->blackListElements_)[std::get<0>(element)] = false;
}

TupleIntDouble PriorityQueue::top() {
    if (this->theQueue_->empty()) {
        throw Exception(__FILE__, __LINE__, "Can not get the top element of an empty stack");
    }
    else {
        TupleIntDouble element = this->theQueue_->top();
        if ((*this->blackListElements_)[std::get<0>(element)] == true) {
            this->pop();
            return this->top();
        }
        else {
            return element;
        }
    }
}

void PriorityQueue::pop() {
    TupleIntDouble element = this->top();
    this->theQueue_->pop();
    (*this->blackListElements_)[std::get<0>(element)];
}

void PriorityQueue::erase(int element) {
    (*this->blackListElements_)[element] = true;
}

bool PriorityQueue::empty() {
    return this->theQueue_->empty();
}

int PriorityQueue::size() {
    return this->theQueue_->size();
}

PriorityQueue::~PriorityQueue() {
    delete this->theQueue_;
    delete this->blackListElements_;
}
