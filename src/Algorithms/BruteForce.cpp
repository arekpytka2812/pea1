#include "../../inc/Algorithms/BruteForce.h"

BruteForce::BruteForce(size_t citiesNumber_)
    : citiesNumber(citiesNumber_)
{
    this->setupVariables();
}

void BruteForce::setupVariables()
{    
    this->optimalPath.reserve(this->citiesNumber - 1);

    this->returnPath = new Path(this->citiesNumber);
}

Path* BruteForce::solveTSP(const AdjacencyMatrix * matrix_, size_t startCity_)
{
    this->startCity = startCity_;

    this->fillupPermutationsVector();

    do
    {
        this->calculateCost(matrix_);
        this->compareCosts();

    } while (std::next_permutation(permutations.begin(), permutations.end()));

    this->createAndFillReturnPath();

    return returnPath;
}

void BruteForce::fillupPermutationsVector()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i != this->startCity)
        {
            this->permutations.push_back(i);
        }
    }
        
}

void BruteForce::calculateCost(const AdjacencyMatrix * matrix_)
{
    this->currentCost = 0;

    // adding cost from start city to first destination
    this->currentCost += matrix_->getValue(this->startCity, this->permutations[0]);

    for(int i = 0; i < this->permutations.size() - 1; ++i)
    {
        this->currentCost += matrix_->getValue(this->permutations[i], this->permutations[i + 1]);
    }

    // adding cost from last visited city to start city
    this->currentCost += matrix_->getValue(this->permutations[this->permutations.size() - 1], this->startCity);
}

void BruteForce::compareCosts()
{
    if(this->currentCost >= this->minimalCost)
        return;

    this->setupNewOptimalPath();
}

void BruteForce::setupNewOptimalPath()
{
    this->minimalCost = this->currentCost;

    for(int i = 0; i < this->permutations.size(); ++i)
    {
        this->optimalPath[i] = this->permutations[i];        
    }

}

void BruteForce::createAndFillReturnPath()
{
    // adding start city to path
    this->returnPath->addCity(this->startCity);

    // adding cities from optimal path
    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        this->returnPath->addCity(this->optimalPath[i]);   
    }

    // adding start city once again
    this->returnPath->addCity(this->startCity);

    // setting up minimal cost
    this->returnPath->setTotalCost(this->minimalCost);
}