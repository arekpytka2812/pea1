#pragma once

#include "TSPSolver.h"

#include "../Enums/CrossoverType.h"

#include "../Structures/Individual.h"

#include <vector>
#include <algorithm>

class GeneticAlgorithm : public TSPSolver
{
public:

    GeneticAlgorithm() = default;

    Path * solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_ = 0) override;

private:

    size_t sourceCity{0};
    size_t citiesNumber{0};

    Array<size_t> optimalPath;
    size_t optimalCost{INT_MAX};

    std::vector<Individual> population;

    static double mutationPropability;
    static double crossoverPropability;
    static size_t populationSize;

    static MutationType mutationType;
    static CrossoverType crossoverType;

    static double stopTime;
    Timer timer;

    void setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_) override;

    void generateFirstPopulation(const AdjacencyMatrix & matrix_);
    std::string shuffleChromosome(std::string cities_);

    void crossoverAndMutate(std::vector<Individual> & newPopulation_);

    void clearVariables();

};