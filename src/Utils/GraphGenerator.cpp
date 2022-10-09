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

GraphGenerator::GraphGenerator(const size_t & citiesNumber_)
{
    data = new InsertedData(citiesNumber_);
}

GraphGenerator::~GraphGenerator()
{
    delete this->data;
}

void GraphGenerator::generateData()
{
    if(data != nullptr)
        this->data->deallocateMemory();

    this->data->allocateMemory();
    this->generateValues();
}

void GraphGenerator::printData()
{
    auto tempSize = this->data->getCitiesNumber() * this->data->getCitiesNumber();

    for(int i = 0; i < tempSize; ++i)
    {

        if(i % this->data->getCitiesNumber() == 0)
            std::cout << "\n";

        std::cout << (*this->data)[i] << " ";
    }

    std::cout << "\n";
}