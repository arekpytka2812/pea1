#pragma once

#include "../Structures/AdjacencyMatrix.h"
#include "../Enums/MutationType.h"

#include "../Utils/RandomGenerator.h"

#include <string>

class Individual
{

public:
    Individual(std::string chromosome_);
    ~Individual() = default;

    void calculateFitness(const AdjacencyMatrix & matrix_, size_t source_);
    void mutate(MutationType mutationType_);

    bool operator<(const Individual& other_)
    {
        return this->fitness < other_.fitness;
    }

    int getFitness() const
    {
        return this->fitness;
    }

    std::string getChromosome() const 
    {
        return this->chromosome;
    }

private:
    std::string chromosome;
    int fitness{INT_MAX};


};

