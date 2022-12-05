#pragma once

#include "TSPSolver.h"

class DP : public TSPSolver
{
    size_t sourceCity{0};

    size_t citiesNumber{0};

    size_t finalMask{0};
    size_t startMask{0};

    Path*** subSolutions{nullptr};

    void setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_);
    Path* resolveSubproblem(const AdjacencyMatrix & matrix_, int currentMask_, size_t currentCity_);
    void clearVariables();

public:

    DP() = default;

    Path * solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_ = 0) override;

};