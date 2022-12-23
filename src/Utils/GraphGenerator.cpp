#include "../../inc/Utils/GraphGenerator.h"

void GraphGenerator::generateValues()
{
    (*this->data)[0] = -1;

    auto tempSize = this->data->getCitiesNumber() * this->data->getCitiesNumber();

    for(int i = 1; i < tempSize; ++i)
    {
        if(i % (this->getCitiesNumber() + 1) == 0)
        {
            (*this->data)[i] = -1;
            continue;
        }

        (*this->data)[i] = rand() % 100;
    }
}

GraphGenerator::GraphGenerator(size_t citiesNumber_)
{
    data = new InsertedData(citiesNumber_);
}

GraphGenerator::~GraphGenerator()
{
    delete this->data;
}

void GraphGenerator::generateData(size_t citiesNumber_)
{
    if(data != nullptr)
        this->data->deallocateMemory();

    this->data->allocateMemory(citiesNumber_);
    this->generateValues();
}

void GraphGenerator::printData()
{
    this->data->printData();
}