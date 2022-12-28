#include "../../inc/Algorithms/BruteForce.h"


Path* BruteForce::solveTSP(const AdjacencyMatrix & matrix_, size_t startCity_)
{
    this->setupVariables(matrix_, startCity_);
    
    this->fillupPermutationsVector();

    do
    {
        this->calculateCost(matrix_);
        this->compareCostsAndChangeOptimalPathIfNeeded();

    } while (permutate());

    auto returnPath = this->createAndFillReturnPath();
    this->clearVariables();

    return returnPath;
}

void BruteForce::setupVariables(const AdjacencyMatrix & matrix_, size_t startCity_)
{    
    this->minimalCost = INT_MAX;
    this->currentCost = 0;

    this->citiesNumber = matrix_.citiesNumber;
    this->startCity = startCity_;

    this->optimalPath.reserve(this->citiesNumber - 1);

}

void BruteForce::fillupPermutationsVector()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i != this->startCity)
            this->permutations.addEnd(i);
    }   
}

void BruteForce::calculateCost(const AdjacencyMatrix & matrix_)
{
    this->currentCost = 0;

    this->currentCost += matrix_.getValue(this->startCity, this->permutations[0]);

    for(int i = 0; i < this->permutations.size() - 1; ++i)
    {
        this->currentCost += matrix_.getValue(this->permutations[i], this->permutations[i + 1]);
    }

    this->currentCost += matrix_.getValue(this->permutations[this->permutations.size() - 1], this->startCity);
}

void BruteForce::compareCostsAndChangeOptimalPathIfNeeded()
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

bool BruteForce::permutate()
{
    size_t size {this->permutations.size()}; 
    int firstSmaller{0}, firstBigger{0};

    // itering from backward to find first ith element smaller
    // than (i + 1)th
    for(firstSmaller = size - 2; firstSmaller > -1; --firstSmaller)
    {
        if(this->permutations[firstSmaller] < this->permutations[firstSmaller + 1])
            break;
    }

    // this means that we have last permutations 
    if(firstSmaller < 0)
    {
        this->permutations.reverse(0, size - 1);
        return false;
    }
        
    // itering from backward to find first element that is bigger
    // than firstSmaller element
    for(firstBigger = size - 1; firstBigger > firstSmaller; --firstBigger)
    {
        if(this->permutations[firstBigger] > this->permutations[firstSmaller])
            break;
    }

    // swapping two found elements
    this->permutations.swap(firstSmaller, firstBigger);
    
    // reversing substring after the first smaller element
    this->permutations.reverse(firstSmaller + 1, size - 1);

    return true;
}

Path* BruteForce::createAndFillReturnPath()
{
    Path* returnPath = new Path();

    returnPath->addCityAtEnd(this->startCity);

    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        returnPath->addCityAtEnd(this->optimalPath[i]);   
    }

    returnPath->addCityAtEnd(this->startCity);

    returnPath->setTotalCost(this->minimalCost);

    return returnPath;
}

void BruteForce::clearVariables()
{
    this->optimalPath.clear();
    this->permutations.clear();
}
