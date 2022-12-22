#include "../../inc/Algorithms/GeneticAlgorithm.h"

double GeneticAlgorithm::mutationPropability{0.1};
double GeneticAlgorithm::crossoverPropability{0.1};
size_t GeneticAlgorithm::populationSize{10};

MutationType GeneticAlgorithm::mutationType{MutationType::Insert};
CrossoverType GeneticAlgorithm::crossoverType{CrossoverType::PMX};
double GeneticAlgorithm::stopTime{10};


Path * GeneticAlgorithm::solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    double algorithmTime{0.0};

    setupVariables(matrix_, sourceCity_);

    timer.startTimer();

    generateFirstPopulation(matrix_);

    std::sort(population.begin(), population.end());

    algorithmTime += timer.stopTimer();

    // while((algorithmTime / 1000.0) < stopTime)
    // {
    //     timer.startTimer();

    //     std::vector<Individual> newPopulation;

    //     crossoverAndMutate(newPopulation);

    //     this->population = newPopulation;

    //     algorithmTime += timer.stopTimer();
    // }

    for(int i = 0; i < 5; ++i)
    {
        timer.startTimer();

        std::vector<Individual> newPopulation;

        crossoverAndMutate(newPopulation);

        this->population = newPopulation;

        algorithmTime += timer.stopTimer();
    }


    auto returnPath = new Path(optimalCost, optimalPath);

    clearVariables();

    return returnPath;
}

void GeneticAlgorithm::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{       
    this->sourceCity = sourceCity_;
    this->citiesNumber = matrix_.citiesNumber;
}

void GeneticAlgorithm::generateFirstPopulation(const AdjacencyMatrix & matrix_)
{
    std::string cities;

    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i == this->sourceCity)
            continue;

        cities.append(std::to_string(i));
    }
    
    for(int i = 0; i < populationSize; ++i)
    {
        std::string chromosome = shuffleChromosome(cities);
        
        Individual individual(chromosome);
        individual.calculateFitness(matrix_, this->sourceCity);

        this->population.push_back(individual);
    }
    
}

std::string GeneticAlgorithm::shuffleChromosome(std::string cities_)
{
    std::string chromosome = cities_;

    for(int i = 0; i < chromosome.size(); ++i)
    {
        auto firstIndex = RandomGenerator::getInt(0, chromosome.size() - 1);
        auto secondIndex = RandomGenerator::getInt(0, chromosome.size() - 1);

        std::swap(chromosome[firstIndex], chromosome[secondIndex]);
    }

    return chromosome;
}


void GeneticAlgorithm::crossoverAndMutate(std::vector<Individual> & newPopulation_)
{
    for(int i = 0; i < populationSize - 1; ++i)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);


        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > mutationPropability)
            continue;

        std::cout << this->population[i].getChromosome() << "\n";

        this->population[i].mutate(mutationType);

        std::cout << this->population[i].getChromosome() << "\n";
    }
}


void GeneticAlgorithm::clearVariables()
{

}