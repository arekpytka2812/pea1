#include "../../inc/Structures/PriorityQueue.h"

PriorityQueue::~PriorityQueue()
{
    
}

void PriorityQueue::push(size_t city_, int cost_)
{
    auto tempNode = new QueueNode(city_, cost_);
    auto current = this->nodes;

    if(this->size == 0)
    {
        this->nodes = tempNode;
        this->size++;
        return;
    }

    if(this->size == 1)
    {
        this->size++;

        if((*current) < (*tempNode))
        {
            current->setNextNode(tempNode);
        }
        else
        {   
            tempNode->setNextNode(current);
            this->nodes = tempNode;
        }

        return;
        
    }

    if(!(*current < *tempNode))
    {
        this->size++;
        tempNode->setNextNode(current);
        this->nodes = tempNode;
        return;
    }

    while(current->getNext() != nullptr && (*(current)->getNext()) < (*tempNode))
    { 
        current = current->getNext();
    }

    auto tempNext = current->getNext();

    current->setNextNode(tempNode);
    tempNode->setNextNode(tempNext);

    this->size++;
}


QueueNode& PriorityQueue::top()
{
    return *(this->nodes);
}

void PriorityQueue::pop()
{
    auto oldHead = this->nodes;

    this->nodes = this->nodes->getNext();

    this->size--;

    delete oldHead;
}

void PriorityQueue::clear()
{
    auto current = this->nodes;
    QueueNode* next = nullptr;
    

    while(current != nullptr)
    {
        next = current->getNext();
        delete current;
        current = next;
    }

    this->size = 0;

    this->nodes = nullptr;
}

void PriorityQueue::printQueue()
{
    auto current = this->nodes;

    while(current != nullptr)
    {
        current->printInfo();
        current = current->getNext();
    }
}