#pragma once

#include "../Utils/RandomGenerator.h"
#include "../Utils/Timer.h"

#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"

class TSPSolver
{
protected:
    virtual void setupVariables(const AdjacencyMatrix& matrix_, size_t sourceCity_) = 0;
    virtual void clearVariables() = 0;
public:

    virtual Path* solveTSP(const AdjacencyMatrix & matrix_, size_t startCity_ = 0) = 0;


};