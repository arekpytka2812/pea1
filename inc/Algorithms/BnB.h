#pragma once

#include "../Structures/AdjacencyMatrix.h"
#include "../Structures/Path.h"
#include "../Structures/PriorityQueue.h"


class BnB
{
    AdjacencyMatrix* copiedMatrix{nullptr};
    size_t citiesNumber{0};
    size_t sourceCity{0};

    int finalMask{0};
    int startMask{0};

    size_t upperBound{INT_MAX};
    Array<size_t> optimalPath;
    Array<size_t> currentPath;

    void setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_);
    void calculateUpperBound();
    int findClosestNeighbour(size_t row_, bool *visited_);
    
    void examineLevel(size_t currentCity_, int currentMask_, int lowerBound_, int level);
    
    void fillQueue(PriorityQueue & queue_, size_t currentCity_, int  currentMask_);
    void setNewOptimalPath();
    
    Path* createReturnPath();
    void clearVariables();

public:

    BnB() = default;
    Path* solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_ = 0);
};