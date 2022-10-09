#include "../inc/Path.h"

void Path::allocateMemory()
{
    this->cities = new size_t[this->citiesNumber + 1];
}

void Path::deallocateMemory()
{
    delete[] this->cities;
    this->cities = nullptr;
}

Path::Path(const size_t & citiesNumber_)
    : citiesNumber(citiesNumber_)
{
    this->allocateMemory();
}

Path::~Path()
{
    this->deallocateMemory();
}

void Path::addCity(const size_t & city_, const size_t & travelCost_)
{
    this->cities[this->citiesCounter] = city_;
    this->totalCost += travelCost_;
    this->citiesCounter++;
}

void Path::printPathInfo()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        std::cout << "| " << this->cities[i] << " | -> ";
    }

    std::cout << "| " << this->cities[this->citiesCounter] << " |\n";

    std::cout << "Total cost: " << this->totalCost << "n";
}