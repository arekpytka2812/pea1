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

void InsertedData::deallocateMemory()
{
    delete[] this->data;
    this->data = nullptr;
}

int & InsertedData::operator[](const size_t & index_)
{
    if(index_ < 0 || index_ > this->citiesNumber - 1)
        return;

    return this->data[index_];
}

