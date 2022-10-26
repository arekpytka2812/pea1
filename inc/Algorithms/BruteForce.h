#pragma once

#include "../Path.h"
#include "../AdjacencyMatrix.h"

#include<vector>
#include<algorithm>

class BruteForce
{
    const size_t citiesNumber{0};
    size_t startCity{0};

    std::vector<int> permutations;
    size_t currentCost{0};
    
    size_t minimalCost{INT_MAX};
    std::vector<int> optimalPath;

    Path * returnPath {nullptr};

    void setupVariables();
    void fillupPermutationsVector();    

    void calculateCost(const AdjacencyMatrix * matrix_);
    void compareCosts();

    void setupNewOptimalPath();

    void createAndFillReturnPath();

public:

    BruteForce(size_t citiesNumber_);
    ~BruteForce();

    Path* solveTSP(const AdjacencyMatrix * matrix_, size_t startCity_ = 0);
};