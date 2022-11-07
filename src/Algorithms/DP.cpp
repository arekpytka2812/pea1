#include "../../inc/Algorithms/DP.h"

Path* DP::solveTSP(const AdjacencyMatrix *matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    auto returnPath = this->resolveSubproblem(this->startMask, this->sourceCity);

    return new Path(*returnPath);

}

void DP::setupVariables(const AdjacencyMatrix * matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;

    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = matrix_->citiesNumber;

    this->finalMask = (1 << this->citiesNumber) - 1; // 1..1
    this->startMask = (1 << this->sourceCity); // 0..01
    
    this->memorizationMatrix = new int*[(1 << this->citiesNumber)];

    for(int i = 0; i < (1 << this->citiesNumber); ++i)
    {
        this->memorizationMatrix[i] = new int[this->citiesNumber];

        for(int j = 0; j < (this->citiesNumber); ++j)
        {
            this->memorizationMatrix[i][j] = -1;
        }
    }

    this->subSolutions = new Path**[this->citiesNumber];
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        this->subSolutions[i] = new Path*[(1 << this->citiesNumber) - 1]{};
    }

}

Path* DP::resolveSubproblem(int currentMask_, size_t currentCity_)
{

    int answer = INT_MAX;

    if(currentMask_ == this->finalMask)
    {
        auto path = new Path();
        path->addCityAtFront(currentCity_, this->copiedMatrix->getValue(currentCity_, 0));
        path->addCityAtEnd(0);
        return path;
    }

    Path* solutionToCheck = this->subSolutions[currentCity_][currentMask_];

    if(solutionToCheck != nullptr)
        return new Path(*solutionToCheck);

    solutionToCheck = new Path();
    solutionToCheck->addCityAtFront(INT_MAX, INT_MAX);

    for(size_t i = 0; i < this->citiesNumber; ++i)
    {
        if(currentMask_ & (1 << i))
            continue;

        auto path = resolveSubproblem(currentMask_ | (1 << i), i);

        auto cost = this->copiedMatrix->getValue(currentCity_, i);

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

    this->subSolutions[currentCity_][currentMask_] = solutionToCheck;

    return new Path(*solutionToCheck);

}
