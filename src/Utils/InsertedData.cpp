#include "../../inc/Utils/InsertedData.h"

InsertedData::InsertedData(const int & citiesNumber_)
    : citiesNumber(citiesNumber_)
{
    this->allocateMemory();
}

InsertedData::~InsertedData()
{
    this->deallocateMemory();
}

void InsertedData::allocateMemory()
{
    auto tempSize = this->citiesNumber * this->citiesNumber;
    data = new int[tempSize] {0};
}

void InsertedData::allocateMemory(size_t citiesNumber_)
{
    this->citiesNumber = citiesNumber_;
    auto tempSize = this->citiesNumber * this->citiesNumber;
    data = new int[tempSize] {0};
}

void InsertedData::deallocateMemory()
{
    delete[] this->data;
    this->data = nullptr;
}

int & InsertedData::operator[](const size_t & index_)
{
    return this->data[index_];
}

void InsertedData::printData()
{
    auto tempSize = this->citiesNumber * this->citiesNumber;

    for(int i = 0; i < tempSize; ++i)
    {

        if(i % this->citiesNumber == 0)
            std::cout << "\n";

        std::cout << this->data[i] << " ";
    }

    std::cout << "\n";
}