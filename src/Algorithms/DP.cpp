#include "../../inc/Algorithms/DP.h"

Path* DP::solveTSP(const AdjacencyMatrix *matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);
    auto returnPath = this->resolveSubproblem(this->startMask, this->sourceCity);

    return returnPath;

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

    this->subSolutions = new Path**[(1 << this->citiesNumber)];
    for(int i = 0; i < (1 << this->citiesNumber); ++i)
    {
        this->subSolutions[i] = new Path*[this->citiesNumber];
    }

}

Path* DP::resolveSubproblem(int currentMask_, size_t currentCity_)
{

    int answer = INT_MAX;

    if(currentMask_ == this->finalMask)
    {
        auto path = new Path();
        path->addCity(currentCity_, this->copiedMatrix->getValue(currentCity_, 0));
        path->addCity(0);
        return path;
    }

    if(this->subSolutions[currentMask_][currentCity_] != nullptr)
        return this->subSolutions[currentMask_][currentCity_];

    
    Path* solutionToCheck = new Path();
    
    // for(int i = 0; i < this->citiesNumber; ++i)
    // {
    //     if(currentMask_ & (1 << i))
    //         continue;
        


    //     int newAnswer = this->copiedMatrix->getValue(currentCity_, i) 
    //         + resolveSubproblem(currentMask_ | (1 << i), i);

    //     answer = std::min(answer, newAnswer);

    //     this->memorizationMatrix[currentMask_][currentCity_] = answer;
    // }

    // return this->memorizationMatrix[currentMask_][currentCity_];

}
