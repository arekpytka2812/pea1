#pragma once

#include "TSPSolver.h"

class BruteForce : public TSPSolver
{
    size_t citiesNumber{0};
    size_t startCity{0};

    Array<size_t> permutations;
    size_t currentCost{0};
    
    size_t minimalCost{INT_MAX};
    Array<size_t> optimalPath;


    void setupVariables(const AdjacencyMatrix & matrix_, size_t startCity_) override;
    void fillupPermutationsVector();    

    void calculateCost(const AdjacencyMatrix & matrix_);
    void compareCostsAndChangeOptimalPathIfNeeded();

    void setupNewOptimalPath();

    bool permutate();

    Path* createAndFillReturnPath();
    
    void clearVariables() override;

public:

    BruteForce() = default;

    Path* solveTSP(const AdjacencyMatrix & matrix_, size_t startCity_ = 0) override;
};