#pragma once

#include "../Path.h"

#include "../AdjacencyMatrix.h"

#include "../Array.hpp"
#include "../../src/Array.tpp"

class DP
{
    static size_t sourceCity;
    static size_t currentCity;

    static AdjacencyMatrix * matrix;
    static size_t citiesNumber; 

    static bool * visited;
    static Path * resultPath;
    static Array<int> * set;

    static void setupVariables();
    static void deallocateOldVariables();
    static void allocateNewVariables();
    static void initializeSet();

    static void findSolution();
    static void calculateCost(Array<int> set_, size_t currentCity_);

public:
    static Path * solveTSP(AdjacencyMatrix * matrix_);

};