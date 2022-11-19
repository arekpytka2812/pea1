#pragma once

#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"

class DP
{
    size_t sourceCity{0};

    AdjacencyMatrix *copiedMatrix{nullptr};
    size_t citiesNumber{0};

    size_t finalMask{0};
    size_t startMask{0};

    Path*** subSolutions{nullptr};

    void setupVariables(const AdjacencyMatrix * matrix_, size_t sourceCity_);
    Path* resolveSubproblem(int currentMask_, size_t currentCity_);
    void clearVariables();

public:

    DP() = default;

    Path * solveTSP(const AdjacencyMatrix * matrix_, size_t sourceCity_ = 0);

};