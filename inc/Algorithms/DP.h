#pragma once

#include "../Path.h"
#include "../AdjacencyMatrix.h"

#include "../Array.hpp"
#include "../../src/Array.tpp"

class DP
{
    size_t sourceCity{0};

    AdjacencyMatrix *copiedMatrix{nullptr};
    size_t citiesNumber{0};

    Array<size_t> set;

    bool *visited{nullptr};

    void setupVariables(const AdjacencyMatrix *matrix_, size_t sourceCity_);
    void fillCitiesSet();
    void executeTSP(Array<size_t> set_, size_t currentCity_);
public:

    DP() = default;

    Path * solveTSP(const AdjacencyMatrix * matrix_, size_t sourceCity_ = 0);

};