#pragma once

#include <iostream>

class Path
{
    size_t citiesNumber{0};
    size_t totalCost{0};

    size_t citiesCounter {0};

    size_t* cities {nullptr};

    void allocateMemory();
    void deallocateMemory();

public:

    explicit Path(const size_t & citiesNumber_);
    ~Path();

    void addCity(const size_t & city_);
    void printPathInfo();
    
    void setTotalCost(const size_t & totalCost_)
    {
        this->totalCost = totalCost_;
    }
    

};