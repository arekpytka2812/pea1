#pragma once

#include <iostream>

#include "Array.hpp"
#include "../../src/Structures/Array.tpp"

class Path
{
    size_t totalCost{0};
    Array<size_t> cities;

    void allocateMemory();
    void deallocateMemory();

public:

    Path();
    Path(size_t totalCost_, const Array<size_t> & cities_);
    ~Path();

    void addCityAtFront(size_t city_, size_t cost_ = 0);
    void addCityAtEnd(size_t city_, size_t cost_ = 0);
    void printPathInfo();
    
    void setTotalCost(size_t totalCost_)
    {
        this->totalCost = totalCost_;
    }

    size_t getTotalCost() const 
    {
        return this->totalCost;
    }
    

};