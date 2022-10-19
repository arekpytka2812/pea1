#include "../inc/Path.h"

void Path::allocateMemory()
{
    this->cities = new size_t[this->citiesNumber + 2];
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

void Path::addCity(const size_t & city_)
{
    this->cities[this->citiesCounter] = city_;
    this->citiesCounter++;
}

void Path::printPathInfo()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        std::cout << "| " << this->cities[i] << " | -> ";
    }

    std::cout << "| " << this->cities[this->citiesNumber] << " |\n";

    std::cout << "Total cost: " << this->totalCost << "\n";
}