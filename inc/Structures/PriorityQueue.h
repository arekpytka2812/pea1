#pragma once

#include "QueueNode.h"


class PriorityQueue
{
    QueueNode* nodes{nullptr};
    size_t size{0};

public:

    PriorityQueue() = default;
    ~PriorityQueue();

    void push(size_t city_, int cost_);
    QueueNode& top();
    void pop();

    bool isEmpty() const
    {
        return this->size ? false : true;
    }

    void clear();

    void printQueue();
};