#include "../../inc/Algorithms/BnB.h"

Path* BnB::solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    this->examineLevel(matrix_, this->sourceCity, this->startMask, 0, 0);

    auto returnPath = this->createReturnPath();

    this->clearVariables();

    return returnPath;
}

void BnB::setupVariables(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;
    this->citiesNumber = matrix_.citiesNumber;

    this->optimalPath.reserve(this->citiesNumber + 1);
    this->currentPath.reserve(this->citiesNumber + 1);

    this->finalMask = (1 << this->citiesNumber) - 1;
    this->startMask = (1 << this->sourceCity);
}

void BnB::examineLevel(const AdjacencyMatrix& matrix_, size_t currentCity_, int currentMask_, int lowerBound_, int level)
{
    // base case, if true then we check cost from last city to source city
    // and if it's smaller, we change upperBound and optimal path
    if(currentMask_ == this->finalMask)
    {
        if(lowerBound_ + matrix_.getValue(currentCity_, this->sourceCity) >= this->upperBound)
            return;
        
        this->upperBound = lowerBound_ + matrix_.getValue(currentCity_, this->sourceCity); 
            
        this->currentPath[level] = currentCity_; 
        this->currentPath[level + 1] = this->sourceCity;

        this->setNewOptimalPath();
        
    }
    
    // creating priority queue and filling with unvisited cities 
    PriorityQueue queue;
    this->fillQueue(matrix_, queue, currentCity_, currentMask_);

    // setting up pathtracking
    this->currentPath[level] = currentCity_;

    // main loop, will work until there are still cities in queue
    while(!queue.isEmpty())
    {
        // getting first element from queue
        auto nodeToExamine = queue.top();
        
        // getting city and cost
        auto currentCity = nodeToExamine.getCity();
        auto cost = nodeToExamine.getCost();

        // poping first element
        queue.pop();
        
        // checking if the path is still promising
        if(lowerBound_ + cost >= upperBound)
        {
            queue.clear();
            return;
        }
            
        // executing recursive method
        this->examineLevel(matrix_, currentCity, currentMask_ | (1 << currentCity), lowerBound_ + cost, level + 1);
    }

    return;
    
}

void BnB::fillQueue(const AdjacencyMatrix & matrix_, PriorityQueue & queue_, size_t currentCity_, int currentMask_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(currentMask_ & (1 << i))
            continue;

        queue_.push(i, matrix_.getValue(currentCity_, i));
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
    this->citiesNumber = 0;
    this->finalMask = 0;
    this->startMask = 0;

    this->upperBound = INT_MAX;
    this->optimalPath.clear();
    this->currentPath.clear();
}