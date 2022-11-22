#pragma once

#include <iostream>

class QueueNode
{
    size_t city{0};
    int costToCity{0};

    QueueNode* nextNode{nullptr};

public:
    QueueNode(size_t city_, int costToCity_, QueueNode* next_ = nullptr)
        : city(city_), costToCity(costToCity_), nextNode(next_)
        {}

    ~QueueNode()
    {
        this->city = 0;
        this->costToCity = 0;
        this->nextNode = nullptr;
    }

    void setNextNode(QueueNode* next_)
    {
        this->nextNode = next_;
    }

    QueueNode* getNext() const
    {
        return this->nextNode;
    }

    size_t getCity() const
    {
        return this->city;
    }

    int getCost() const 
    {
        return this->costToCity;
    }

    void printInfo()
    {
        std::cout << "City: " << this->city << " cost: " << this->costToCity << std::endl;
    }

    bool operator<(const QueueNode & node_)
    {
        if(this->costToCity < node_.costToCity)
            return true;
        
        if(this->costToCity == node_.costToCity)
            if(this->city < node_.city)
                return true;
        
        return false;
    }

};