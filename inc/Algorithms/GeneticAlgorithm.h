#pragma once

#include "TSPSolver.h"

#include "../Enums/CrossoverType.h"

#include "../Structures/Individual.h"

#include "../Utils/CrossoverGenerator.h"

#include <vector>
#include <algorithm>

class GeneticAlgorithm : public TSPSolver
{
public:

    GeneticAlgorithm() = default;

    Path * solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_ = 0) override;

    static void setStopTime(double stopTime_)
    {
        stopTime = stopTime_;
    }

    static void setPopulationSize(size_t size_)
    {
        populationSize = size_;
    }

    static void setMutationType(MutationType type_)
    {
        mutationType = type_;
    }

    static void setCrossoverType(CrossoverType type_)
    {
        crossoverType = type_;
    }

    static void setMutationPropability(double propability_)
    {
        mutationPropability = propability_;
    }

    static void setCrossoverPropability(double propability_)
    {
        crossoverPropability = propability_;
    }

private:

    size_t sourceCity{0};
    size_t citiesNumber{0};

    std::vector<int> optimalPath;
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
    std::vector<int> shuffleChromosome(const std::vector<int> & cities_);

    void generateNewPopulation(std::vector<Individual> & newPopulation_);
    void crossover(std::vector<Individual> & newPopulation_);
    void executeCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_);

    void mutate(std::vector<Individual> & newPopulation_);

    void calculatePopulationFitness(const AdjacencyMatrix& matrix_);

    void clearVariables();

};