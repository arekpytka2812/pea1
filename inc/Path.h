#include <iostream>

class Path
{
    size_t citiesNumber;
    size_t totalCost{0};

    size_t citiesCounter {0};

    size_t* cities {nullptr};

    void allocateMemory();
    void deallocateMemory();

public:

    explicit Path(const size_t & citiesNumber_);
    ~Path();

    void addCity(const size_t & city_, const size_t & travelCost_);
    void printPathInfo();

};