#include "../inc/AdjacencyMatrix.h"

void AdjacencyMatrix::allocateMemory()
{
    this->matrix = new int* [this->citiesNumber];

    for(int i = 0; i < this->citiesNumber; ++i)
    {
        this->matrix[i] = new int[this->citiesNumber];

        for(int j = 0; j < this->citiesNumber; ++j)
            this->matrix[i][j] = 0;
    }

}

void AdjacencyMatrix::insertValues(const int* data_)
{
    for(int i = 0, dataCounter = 0; i < this->citiesNumber; ++i)
    {
        for(int j = 0; j < this->citiesNumber; ++j, ++dataCounter)
        {
            this->matrix[i][j] = data_[dataCounter];
        }
    }
}

void AdjacencyMatrix::copyValues(int** dataFromOrigin_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        for(int j = 0; j < this->citiesNumber; ++j)
        {
            this->matrix[i][j] = dataFromOrigin_[i][j];
        }
    }
}

void AdjacencyMatrix::deallocateMemory()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        delete[] this->matrix[i];
    }

    delete[] this->matrix;

    this->matrix = nullptr;
}

AdjacencyMatrix::AdjacencyMatrix(size_t citiesNumber_, const int* data_)
    : citiesNumber(citiesNumber_)
{
    this->allocateMemory();
    this->insertValues(data_);
}

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix & origin_)
    : citiesNumber(origin_.citiesNumber)
{
    this->allocateMemory();
    this->copyValues(origin_.matrix);
}

AdjacencyMatrix::~AdjacencyMatrix()
{
    this->deallocateMemory();
}

void AdjacencyMatrix::printMatrix()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        for(int j = 0; j < this->citiesNumber; ++j)
        {
            std::cout << this->matrix[i][j] << " ";
        }

        std::cout << "\n";
    }
}