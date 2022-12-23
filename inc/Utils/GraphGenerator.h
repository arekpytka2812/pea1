#pragma once

#include "InsertedData.h"

#include <cstdlib>
#include <iostream>

class GraphGenerator
{
    InsertedData *data{nullptr};

    void generateValues();

public:
    
    GraphGenerator() = default;
    explicit GraphGenerator(size_t citiesNumber_);
    ~GraphGenerator();

    void generateData(size_t citiesNumber_);
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