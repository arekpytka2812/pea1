#include "../../inc/Algorithms/BnB.h"

Path* BnB::solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    this->examineLevel(this->sourceCity, this->startMask, 0, 0);

    auto returnPath = this->createReturnPath();

    this->clearVariables();

    return returnPath;
}

void BnB::setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;
    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = copiedMatrix->citiesNumber;

    this->optimalPath.reserve(this->citiesNumber + 1);
    this->currentPath.reserve(this->citiesNumber + 1);

    this->finalMask = (1 << this->citiesNumber) - 1;
    this->startMask = (1 << this->sourceCity);
}

void BnB::calculateUpperBound()
{
    bool *visited = new bool[this->citiesNumber]{false};

    visited[this->sourceCity] = true;

    size_t currentCity = this->sourceCity;
    this->optimalPath.addEnd(this->sourceCity);

    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        auto nextNeighbour = this->findClosestNeighbour(currentCity, visited);

        if(nextNeighbour == -1)
            break;
        
        this->upperBound += this->copiedMatrix->getValue(currentCity, nextNeighbour);
        this->optimalPath.addEnd(nextNeighbour);

        visited[nextNeighbour] = true;
        currentCity = nextNeighbour;
    }

    this->upperBound += this->copiedMatrix->getValue(currentCity, this->sourceCity);
    this->optimalPath.addEnd(this->sourceCity);

    delete[] visited;
}

int BnB::findClosestNeighbour(size_t row_, bool *visited_)
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

void BnB::examineLevel(size_t currentCity_, int currentMask_, int lowerBound_, int level)
{
    if(currentMask_ == this->finalMask)
    {
        if(lowerBound_ + this->copiedMatrix->getValue(currentCity_, this->sourceCity) < this->upperBound)
        {
            this->upperBound = lowerBound_ + this->copiedMatrix->getValue(currentCity_, this->sourceCity); 
            
            this->currentPath[level] = currentCity_; 
            this->currentPath[level + 1] = this->sourceCity;

            this->setNewOptimalPath();
        }

        return;
    }
    
    PriorityQueue queue;
    this->fillQueue(queue, currentCity_, currentMask_);

    this->currentPath[level] = currentCity_;

    while(!queue.isEmpty())
    {
        auto nodeToExamine = queue.top();
        
        auto currentCity = nodeToExamine.getCity();
        auto cost = nodeToExamine.getCost();

        queue.pop();
        
        if(lowerBound_ + cost >= upperBound)
        {
            queue.clear();
            return;
        }
            
        this->examineLevel(currentCity, currentMask_ | (1 << currentCity), lowerBound_ + cost, level + 1);
    }

    return;
    
}

void BnB::fillQueue(PriorityQueue & queue_, size_t currentCity_, int currentMask_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(currentMask_ & (1 << i))
            continue;

        queue_.push(i, this->copiedMatrix->getValue(currentCity_, i));
    }
}

void BnB::setNewOptimalPath()
{
    for(int i = 0; i < this->citiesNumber + 1; ++i)
        this->optimalPath[i] = this->currentPath[i];
}

Path* BnB::createReturnPath()
{
    Path* returnPath = new Path();

    for(int i = 0; i < this->citiesNumber + 1; ++i)
        returnPath->addCityAtEnd(this->optimalPath[i]);

    returnPath->setTotalCost(upperBound);

    return returnPath;
}

void BnB::clearVariables()
{
    delete this->copiedMatrix;

    this->citiesNumber = 0;
    this->finalMask = 0;
    this->startMask = 0;

    this->upperBound = INT_MAX;
    this->optimalPath.clear();
    this->currentPath.clear();
}