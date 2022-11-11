#include "../../inc/Algorithms/BnBsecond.h"

Path* BnBSecond::solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    this->calculateUpperBound();

    std::cout << this->upperBound;
}

void BnBSecond::setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;
    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = copiedMatrix->citiesNumber;
}

void BnBSecond::calculateUpperBound()
{
    bool *visited = new bool[this->citiesNumber]{false};

    visited[this->sourceCity] = true;

    size_t currentCity = this->sourceCity;

    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        auto nextNeighbour = this->findClosestNeighbour(currentCity, visited);

        if(nextNeighbour == -1)
            break;
        
        this->upperBound += this->copiedMatrix->getValue(currentCity, nextNeighbour);

        visited[nextNeighbour] = true;
        currentCity = nextNeighbour;
    }

    this->upperBound += this->copiedMatrix->getValue(currentCity, this->sourceCity);

    delete[] visited;
}

int BnBSecond::findClosestNeighbour(size_t row_, bool *visited_)
{
    auto min{INT_MAX};
    auto indexOfMin{-1};

    for(size_t i = 0; i < this->citiesNumber; ++i)
    {
        if(visited_[i])
            continue;

        if(this->copiedMatrix->getValue(row_, i) < min && this->copiedMatrix->getValue(row_, i) != -1)
        {
            indexOfMin = i;
            min = this->copiedMatrix->getValue(row_, i);
        }
    }

    return indexOfMin;
}