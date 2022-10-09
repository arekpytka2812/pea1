#include <iostream>

class AdjacencyMatrix
{
    size_t citiesNumber;
    int **matrix = nullptr;

    void allocateMemory();
    void insertValues(const int* data_);

    void deallocateMemory();

public:

    AdjacencyMatrix(const size_t & citiesNumber_, const int* data_);
    ~AdjacencyMatrix();

    void printMatrix();
};