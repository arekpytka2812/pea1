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

    this->optimalPath = this->population[0].getChromosome();
    this->optimalCost = this->population[0].getFitness();

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

        generateNewPopulation(newPopulation);

        this->population = newPopulation;

        std::sort(this->population.begin(), this->population.end());

        if(this->optimalCost > this->population[0].getFitness())
        {
            this->optimalCost = this->population[0].getFitness();
            this->optimalPath = this->population[0].getChromosome();
        }

        algorithmTime += timer.stopTimer();
    }


    auto returnPath = new Path(optimalCost, optimalPath);

    returnPath->addCityAtFront(this->sourceCity);
    returnPath->addCityAtEnd(this->sourceCity);

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


void GeneticAlgorithm::generateNewPopulation(std::vector<Individual> & newPopulation_)
{
    crossover(newPopulation_);
    
    mutate(newPopulation_);
}

void GeneticAlgorithm::crossover(std::vector<Individual> & newPopulation_)
{
    for(int i = 0; i < populationSize - 1; i += 2)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > crossoverPropability)
        {
            newPopulation_.push_back(this->population[i]);
            newPopulation_.push_back(this->population[i + 1]);
            continue;
        }
            
        auto chromosome1 = this->population[i].getChromosome();
        auto chromosome2 = this->population[i + 1].getChromosome();

        executeCrossover(chromosome1, chromosome2);

        Individual newInd1(chromosome1);
        Individual newInd2(chromosome2);

        newPopulation_.push_back(newInd1);
        newPopulation_.push_back(newInd2);
    }
}

void GeneticAlgorithm::executeCrossover(std::string & chromosome1_, std::string & chromosome2_)
{
    switch (crossoverType)
    {

        case CrossoverType::PMX:

            CrossoverGenerator::pmxCrossover(chromosome1_, chromosome2_);
   
            break;
    
        case CrossoverType::EX:

            CrossoverGenerator::exCrossover(chromosome1_, chromosome2_);

            break;
    }
}



void GeneticAlgorithm::mutate(std::vector<Individual> & newPopulation_)
{
    for(int i = 0; i < populationSize; ++i)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > mutationPropability)
            continue;

        newPopulation_[i].mutate(mutationType);

    }
}

void GeneticAlgorithm::clearVariables()
{

}