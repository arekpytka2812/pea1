#pragma once

#include "../Path.h"
#include "../AdjacencyMatrix.h"
#include "../Array.hpp"
#include "../../src/Array.tpp"

#include<algorithm>

class BruteForce
{
    size_t citiesNumber{0};
    size_t startCity{0};

    Array<size_t> permutations;
    size_t currentCost{0};
    
    size_t minimalCost{INT_MAX};
    Array<size_t> optimalPath;

    Path * returnPath {nullptr};

    void setupVariables(const AdjacencyMatrix * matrix_, size_t startCity_);
    void fillupPermutationsVector();    

    void calculateCost(const AdjacencyMatrix * matrix_);
    void compareCostsAndChangeOptimalPathIfNeeded();

    void setupNewOptimalPath();

    bool permutate();

    void createAndFillReturnPath();
    

public:

    BruteForce() = default;
    ~BruteForce();

    Path* solveTSP(const AdjacencyMatrix * matrix_, size_t startCity_ = 0);
};