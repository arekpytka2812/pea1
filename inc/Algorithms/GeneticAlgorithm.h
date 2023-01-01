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

    static void setMutationProbability(double probability_)
    {
        mutationProbability = probability_;
    }

    static void setCrossoverProbability(double probability_)
    {
        crossoverProbability = probability_;
    }

private:

    size_t sourceCity{0};
    size_t citiesNumber{0};

    Individual bestOne;

    int bestOnesCrossovers{0};

    std::vector<Individual> population;

    static double mutationProbability;
    static double crossoverProbability;
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