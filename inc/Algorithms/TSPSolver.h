#pragma once

#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"

class TSPSolver
{

public:

    virtual Path* solveTSP(const AdjacencyMatrix & matrix_, size_t startCity_ = 0) = 0;

};