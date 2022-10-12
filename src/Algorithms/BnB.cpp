#include "../../inc/Algorithms/BnB.h"

Path* BnB::solveTSP(AdjacencyMatrix* matrix_)
{
    this->setupVariables(matrix_);
    this->reduceMatrix();
}

void BnB::setupVariables(AdjacencyMatrix* matrix_)
{
    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = copiedMatrix->getCitiesNumber();
}

void BnB::reduceMatrix()
{
    this->reduceRows();
}

void BnB::reduceRows()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        auto minValue = findMinInRow(i);

        for(int j = 0; j < this->citiesNumber; ++j)
        {
            this->copiedMatrix->getMatrix()[i][j] -= minValue;
        }
    }
}

bool BnB::isZeroInRow(const size_t & row_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(this->copiedMatrix->getValue(row_, i) == 0)
            return true;
    }

    return false;
}