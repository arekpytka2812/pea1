#include <iostream>

class AdjacencyMatrix
{
    size_t citiesNumber;
    int **matrix = nullptr;

    void allocateMemory();
    void insertValues(const int* data_);
    void copyValues(const int** dataFromOrigin_);

    void deallocateMemory();

public:

    AdjacencyMatrix(const size_t & citiesNumber_, const int* data_);
    AdjacencyMatrix(const AdjacencyMatrix & origin_);
    ~AdjacencyMatrix();

    int** getMatrix() const
    {
        return this->matrix;
    }

    int getValue(const size_t & source_, const size_t & destination_) const
    {
        return this->matrix[source_][destination_];
    }

    size_t getCitiesNumber() const
    {
        return this->citiesNumber;
    }

    void printMatrix();
};