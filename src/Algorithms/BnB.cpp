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
    this->reduceColumns();
}

void BnB::reduceRows()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        auto minValue = findMinInRow(i);

        for(int j = 0; j < this->citiesNumber; ++j)
        {
            if(this->copiedMatrix->getMatrix()[i][j] != -1)
                this->copiedMatrix->getMatrix()[i][j] -= minValue;
        }

        this->minimumCost += minValue;
    }
}

void BnB::reduceColumns()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(this->isZeroInColumn(i))
            continue;

        auto minValue = findMinInColumn(i);

        for(int j = 0; j < this->citiesNumber; ++j)
        {
            if(this->copiedMatrix->getMatrix()[j][i] != -1)
                this->copiedMatrix->getMatrix()[j][i] -= minValue;
        }

        this->minimumCost += minValue;

    }
}

bool BnB::isZeroInColumn(const size_t & column_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(this->copiedMatrix->getValue(i, column_) == 0)
            return true;
    }

    return false;
}

int BnB::findMinInColumn(const size_t & column_)
{
    int minValue = INT_MAX;

    for(int i = 0; i < this->citiesNumber; ++i)
    {
        auto cellValue = this->copiedMatrix->getValue(i, column_);

        if(cellValue < minValue && cellValue != -1)
        {
            minValue = cellValue;
        }
    }

    return minValue;
}

int BnB::findMinInRow(const size_t & row_)
{
    int minValue = INT_MAX;

    for(int i = 0; i < this->citiesNumber; ++i)
    {
        auto cellValue = this->copiedMatrix->getValue(row_, i);

        if(cellValue < minValue && cellValue != -1)
        {
            minValue = cellValue;
        }
    }

    return minValue;
}