#pragma once

#include "../AdjacencyMatrix.h"
#include "../Path.h"
#include "../PriorityQueue.h"

class BnBSecond
{
    AdjacencyMatrix* copiedMatrix{nullptr};
    size_t citiesNumber{0};
    size_t sourceCity{0};

    int finalMask{0};
    int startMask{0};

    size_t upperBound{0};
    Array<size_t> optimalPath;

    void setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_);
    void calculateUpperBound();
    int findClosestNeighbour(size_t row_, bool *visited_);
    
    void examineLevel(size_t sourceCity_, int currentMask_, int lowerBound_);
    void fillQueue(PriorityQueue & queue_, size_t currentCity_, int  currentMask_);

    void clearVariables();

public:

    BnBSecond() = default;
    Path* solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_ = 0);
};