#pragma once

#include "../Path.h"
#include "../AdjacencyMatrix.h"
#include "../Array.hpp"
#include "../../src/Array.tpp"

#include<vector>
#include<algorithm>

class BruteForce
{
    const size_t citiesNumber{0};
    size_t startCity{0};

    Array<size_t> permutations;
    size_t currentCost{0};
    
    size_t minimalCost{INT_MAX};
    Array<size_t> optimalPath;

    Path * returnPath {nullptr};

    void setupVariables();
    void fillupPermutationsVector();    

    void calculateCost(const AdjacencyMatrix * matrix_);
    void compareCosts();

    void setupNewOptimalPath();

    void createAndFillReturnPath();

    bool permutate();

public:

    BruteForce(size_t citiesNumber_);
    ~BruteForce();

    Path* solveTSP(const AdjacencyMatrix * matrix_, size_t startCity_ = 0);
};