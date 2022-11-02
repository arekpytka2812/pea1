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

    } while (permutate());

    this->createAndFillReturnPath();

    return returnPath;
}

void BruteForce::fillupPermutationsVector()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i != this->startCity)
            this->permutations.addEnd(i);
    }   
}

void BruteForce::calculateCost(const AdjacencyMatrix * matrix_)
{
    this->currentCost = 0;

    this->currentCost += matrix_->getValue(this->startCity, this->permutations[0]);

    for(int i = 0; i < this->permutations.size() - 1; ++i)
    {
        this->currentCost += matrix_->getValue(this->permutations[i], this->permutations[i + 1]);
    }

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
    
    this->returnPath->addCity(this->startCity);

    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        this->returnPath->addCity(this->optimalPath[i]);   
    }

    this->returnPath->addCity(this->startCity);

    this->returnPath->setTotalCost(this->minimalCost);
}

bool BruteForce::permutate()
{
    int size {this->permutations.size()}, k{0}, l{0};

    for(k = size - 2; k > -1; --k)
    {
        if(this->permutations[k] < this->permutations[k + 1])
            break;
    }

    if(k < 0)
        return false;

    for(l = size - 1; l > k; --l)
    {
        if(this->permutations[l] > this->permutations[k])
            break;
    }

    this->permutations.swap(k, l);
    this->permutations.reverse(k + 1, size - 1);

    return true;
}