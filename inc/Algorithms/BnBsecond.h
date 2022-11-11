#pragma once

#include "../AdjacencyMatrix.h"
#include "../Path.h"

// #include "../Array.hpp"
// #include "../../src/Array.tpp"

class BnBSecond
{
    AdjacencyMatrix* copiedMatrix{nullptr};
    size_t citiesNumber{0};
    size_t sourceCity{0};

    size_t upperBound{0};
    // Array<size_t> optimalPath;

    void setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_);
    void calculateUpperBound();
    int findClosestNeighbour(size_t row_, bool *visited_);
    void clearVariables();

public:

    BnBSecond() = default;
    Path* solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_ = 0);
};