#include "InsertedData.h"

#include <cstdlib>
#include <iostream>

class GraphGenerator
{
    InsertedData *data;

    void generateValues();

public:
    
    explicit GraphGenerator(size_t citiesNumber_);
    ~GraphGenerator();

    void generateData();
    void printData();

    size_t getCitiesNumber() const
    {
        return this->data->getCitiesNumber();
    }

    int* getData() const
    {
        return this->data->getData();
    }
};