#pragma once

#include <iostream>

#include "Array.hpp"
#include "../src/Array.tpp"

class Path
{
    size_t totalCost{0};
    Array<size_t> cities;

    void allocateMemory();
    void deallocateMemory();

public:

    Path();
    ~Path();

    void addCity(size_t city_, size_t cost_ = 0);
    void printPathInfo();
    
    void setTotalCost(size_t totalCost_)
    {
        this->totalCost = totalCost_;
    }
    

};