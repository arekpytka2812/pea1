#pragma once

#include <iostream>

class AdjacencyMatrix
{
    
    int **matrix = nullptr;
    
    void allocateMemory();
    void insertValues(const int* data_);
    void copyValues(int** dataFromOrigin_);

    void deallocateMemory();

public:

    const size_t citiesNumber;

    AdjacencyMatrix(size_t citiesNumber_, const int* data_);
    AdjacencyMatrix(const AdjacencyMatrix & origin_);
    ~AdjacencyMatrix();

    int** getMatrix() const
    {
        return this->matrix;
    }

    int getValue(size_t source_, size_t destination_) const
    {
        return this->matrix[source_][destination_];
    }

    void printMatrix();
};