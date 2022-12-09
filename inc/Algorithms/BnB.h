#pragma once

#include "TSPSolver.h"
#include "../Structures/PriorityQueue.h"


class BnB : TSPSolver
{
    size_t citiesNumber{0};
    size_t sourceCity{0};

    int finalMask{0};
    int startMask{0};

    size_t upperBound{INT_MAX};
    Array<size_t> optimalPath;
    Array<size_t> currentPath;

    void setupVariables(const AdjacencyMatrix& matrix_, size_t sourceCity_) override;
  
    void examineLevel(const AdjacencyMatrix& matrix_, size_t currentCity_, int currentMask_, int lowerBound_, int level);
    
    void fillQueue(const AdjacencyMatrix & matrix_, PriorityQueue & queue_, size_t currentCity_, int  currentMask_);
    void setNewOptimalPath();
    
    Path* createReturnPath();
    void clearVariables() override;

public:

    BnB() = default;
    Path* solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_ = 0) override;
};