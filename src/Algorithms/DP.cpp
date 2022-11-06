#include "../../inc/Algorithms/DP.h"

Path* DP::solveTSP(const AdjacencyMatrix *matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    this->executeTSP(this->set, this->sourceCity);

}

void DP::setupVariables(const AdjacencyMatrix *matrix_, size_t sourceCity_)
{
    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = matrix_->citiesNumber;
    this->visited = new bool[this->citiesNumber]{false};

    this->fillCitiesSet();
}

void DP::fillCitiesSet()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {

    }
}

void DP::executeTSP(Array<size_t> set_, size_t currentCity_)
{
    visited[currentCity_] = true;

    if(set_.size() == 2)
        return;
}