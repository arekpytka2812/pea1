#pragma once

#include "GraphGenerator.h"
#include "FileReader.h"

#include "../Algorithms/BruteForce.h"
#include "../Algorithms/DP.h"
#include "../Algorithms/BnB.h"
#include "../Algorithms/SimulatedAnnealing.h"
#include "../Algorithms/TabuSearch.h"
#include "../Algorithms/GeneticAlgorithm.h"

class Tests
{
    AdjacencyMatrix* matrix {nullptr};
    Path* returnPath {nullptr};

    FileWritter fileWritter;
    FileReader fileReader;
    Timer timer;

    void task1Tests();
    void generateInstance(GraphGenerator& gg_, size_t size_);

    void task2Tests();

    void task3Tests();

    void task3PopulationsSizeTest();
    void task3CrossoverProbTest();
    void task3MutationProbTest();

public:

    Tests();
    ~Tests();

    void performAutoTests();
};