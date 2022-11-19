#pragma once

#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"


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
    
    void clearVariables();

public:

    BruteForce() = default;
    ~BruteForce();

    Path* solveTSP(const AdjacencyMatrix * matrix_, size_t startCity_ = 0);
};