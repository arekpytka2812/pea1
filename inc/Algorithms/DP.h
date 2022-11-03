#pragma once

#include "../Path.h"
#include "../AdjacencyMatrix.h"

#include "../Array.hpp"
#include "../../src/Array.tpp"

class DP
{
    size_t sourceCity{0};

    AdjacencyMatrix *copiedMatrix{nullptr};
    size_t citesNumber{0};

    bool *visited{nullptr};

public:

    DP() = default;

    Path * solveTSP(AdjacencyMatrix * matrix_);

};