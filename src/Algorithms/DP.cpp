#include "../../inc/Algorithms/DP.h"

Path* DP::solveTSP(const AdjacencyMatrix &matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    auto returnPath = this->resolveSubproblem(matrix_, this->startMask, this->sourceCity);

    this->clearVariables();

    return new Path(*returnPath);

}

void DP::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;

    this->citiesNumber = matrix_.citiesNumber;

    this->finalMask = (1 << this->citiesNumber) - 1; // 1..1
    this->startMask = (1 << this->sourceCity); // 0..01

    this->subSolutions = new Path**[this->citiesNumber];
    
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        this->subSolutions[i] = new Path*[(1 << this->citiesNumber) - 1]{};
    }

}

Path* DP::resolveSubproblem(const AdjacencyMatrix & matrix_, int currentMask_, size_t currentCity_)
{
    // base case, if we meet our final mask, we add cost from last to start city
    if(currentMask_ == this->finalMask)
    {
        auto path = new Path();
        path->addCityAtFront(currentCity_, matrix_.getValue(currentCity_, this->sourceCity));
        path->addCityAtEnd(this->sourceCity);
        return path;
    }

    Path* solutionToCheck = this->subSolutions[currentCity_][currentMask_];

    // if it isnt nullptr that means we have already resolved such problem
    if(solutionToCheck != nullptr)
        return new Path (*solutionToCheck);

    // setting INT_MAX values at start of the loop
    solutionToCheck = new Path();
    solutionToCheck->addCityAtFront(INT_MAX, INT_MAX);

    // ittering through cities
    for(size_t i = 0; i < this->citiesNumber; ++i)
    {
        // if we have already been in such city, we skip this ietraion
        //
        // 01011
        // 00001
        //
        // we have visited 0th city and we can skip this iteraion
        if(currentMask_ & (1 << i))
            continue;

        // calling recursive function
        auto path = resolveSubproblem(matrix_, currentMask_ | (1 << i), i);

        // getting cost from currentCity to ith city
        auto cost = matrix_.getValue(currentCity_, i);

        // if cost + cost of currently resolved problem is smaller than our 
        // "level" solution, we change "level" solution to currently
        // resolved and adding currentCity to the path
        if(cost + path->getTotalCost() < solutionToCheck->getTotalCost())
        {
            delete solutionToCheck;
            solutionToCheck = path;
            solutionToCheck->addCityAtFront(currentCity_, cost);
        } 
        else
        {
            delete path;
        }
    }

    // memorising best solution in subSolutions 2d array
    this->subSolutions[currentCity_][currentMask_] = solutionToCheck;

    return new Path(*solutionToCheck);
}

void DP::clearVariables()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        delete[] this->subSolutions[i];
    }

    delete[] this->subSolutions;

    this->citiesNumber = 0;
    this->finalMask = 0;
    this->startMask = 0;
}
