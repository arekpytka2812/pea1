#include "../../inc/Algorithms/GeneticAlgorithm.h"

double GeneticAlgorithm::mutationProbability{0.0};
double GeneticAlgorithm::crossoverProbability{1.0};
size_t GeneticAlgorithm::populationSize{30};

MutationType GeneticAlgorithm::mutationType{MutationType::Swap};
CrossoverType GeneticAlgorithm::crossoverType{CrossoverType::OX};
double GeneticAlgorithm::stopTime{10};


Path * GeneticAlgorithm::solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    double algorithmTime{0.0};

    setupVariables(matrix_, sourceCity_);

    generateFirstPopulation(matrix_);

    std::sort(population.begin(), population.end());
    this->bestOne = this->population[0];

    while((algorithmTime / 1000.0) < stopTime)
    {
        timer.startTimer();

        std::vector<Individual> newPopulation;

        generateNewPopulation(newPopulation);

        this->population = newPopulation;

        calculatePopulationFitness(matrix_);

        std::sort(this->population.begin(), this->population.end());

        if(this->bestOne.getFitness() > this->population[0].getFitness())
            this->bestOne = this->population[0];

        algorithmTime += timer.stopTimer();
    }

    auto returnPath = new Path(this->bestOne.getFitness(), this->bestOne.getChromosome());

    returnPath->addCityAtFront(this->sourceCity);
    returnPath->addCityAtEnd(this->sourceCity);

    clearVariables();

    return returnPath;
}

void GeneticAlgorithm::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{       
    this->sourceCity = sourceCity_;
    this->citiesNumber = matrix_.citiesNumber;

    this->bestOnesCrossovers = static_cast<int>(0.1 * populationSize);
}

void GeneticAlgorithm::generateFirstPopulation(const AdjacencyMatrix & matrix_)
{
    std::vector<int> cities;

    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i == this->sourceCity)
            continue;

        cities.push_back(i);
    }
    
    for(int i = 0; i < populationSize; ++i)
    {
        std::vector<int> chromosome = shuffleChromosome(cities);
        
        Individual individual(chromosome);
        individual.calculateFitness(matrix_, this->sourceCity);

        this->population.push_back(individual);
    }
    
}

std::vector<int> GeneticAlgorithm::shuffleChromosome(const std::vector<int> & cities_)
{
    std::vector<int> chromosome = cities_;

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

    // best one is always alive until new best one 
    newPopulation_.push_back(this->bestOne);

    for(int i = 1; i < bestOnesCrossovers + 1; ++i)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > crossoverProbability)
        {
            newPopulation_.push_back(this->population[i]);
            continue;
        }

        auto chromosome1 = this->bestOne.getChromosome();
        auto chromosome2 = this->population[i].getChromosome();

        executeCrossover(chromosome1, chromosome2);

        newPopulation_.push_back(Individual(chromosome1));
        newPopulation_.push_back(Individual(chromosome2));
    }

    for(int i = bestOnesCrossovers + 1; i < populationSize - 3; i += 2)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > crossoverProbability)
        {
            newPopulation_.push_back(this->population[i]);
            newPopulation_.push_back(this->population[i + 1]);
            continue;
        }
            
        auto chromosome1 = this->population[i].getChromosome();
        auto chromosome2 = this->population[i + 1].getChromosome();

        executeCrossover(chromosome1, chromosome2);

        newPopulation_.push_back(Individual(chromosome1));
        newPopulation_.push_back(Individual(chromosome2));
    }

    auto preLastChromosome = this->population[this->populationSize - 2].getChromosome();

    newPopulation_.push_back(Individual(preLastChromosome));
}

void GeneticAlgorithm::executeCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_)
{
    switch (crossoverType)
    {

        case CrossoverType::PMX:

            CrossoverGenerator::pmxCrossover(chromosome1_, chromosome2_);
   
            break;
    
        case CrossoverType::OX:

            CrossoverGenerator::oxCrossover(chromosome1_, chromosome2_);

            break;
    }
}

void GeneticAlgorithm::mutate(std::vector<Individual> & newPopulation_)
{
    for(int i = 0; i < populationSize; ++i)
    {
        auto randomPropability = RandomGenerator::getDouble(0.0, 1.0);

        if(randomPropability > mutationProbability)
            continue;

        newPopulation_[i].mutate(mutationType);
    }
}

void GeneticAlgorithm::calculatePopulationFitness(const AdjacencyMatrix& matrix_)
{
    for(auto & individual : this->population)
        individual.calculateFitness(matrix_, this->sourceCity);
}

void GeneticAlgorithm::clearVariables()
{
    this->sourceCity = 0;
    this->citiesNumber = 0;
}

Path * GeneticAlgorithm::solveTSP(std::string fileName_, FileWritter& writter_, const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    double algorithmTime{0.0};

    setupVariables(matrix_, sourceCity_);

    generateFirstPopulation(matrix_);

    std::sort(population.begin(), population.end());
    this->bestOne = this->population[0];

    while((algorithmTime / 1000.0) < stopTime)
    {
        timer.startTimer();

        std::vector<Individual> newPopulation;

        generateNewPopulation(newPopulation);

        this->population = newPopulation;

        calculatePopulationFitness(matrix_);

        std::sort(this->population.begin(), this->population.end());

        if(this->bestOne.getFitness() > this->population[0].getFitness())
        {
            this->bestOne = this->population[0];
            
            algorithmTime += timer.stopTimer();

            writter_.writeGAIntoFile(fileName_, mutationType, mutationProbability, crossoverType, crossoverProbability, algorithmTime, bestOne.getFitness());
        }

        algorithmTime += timer.stopTimer();
    }

    auto returnPath = new Path(this->bestOne.getFitness(), this->bestOne.getChromosome());

    returnPath->addCityAtFront(this->sourceCity);
    returnPath->addCityAtEnd(this->sourceCity);

    clearVariables();

    return returnPath;
}

Path * GeneticAlgorithm::solveTSP(size_t  diff_, std::string fileName_, FileWritter &writter_, const AdjacencyMatrix & matrix_)
{
    double algorithmTime{0.0};

    setupVariables(matrix_, 0);

    generateFirstPopulation(matrix_);

    std::sort(population.begin(), population.end());
    this->bestOne = this->population[0];

    while((algorithmTime / 1000.0) < stopTime)
    {
        timer.startTimer();

        std::vector<Individual> newPopulation;

        generateNewPopulation(newPopulation);
 
        this->population = newPopulation;

        calculatePopulationFitness(matrix_);

        std::sort(this->population.begin(), this->population.end());

        if(this->bestOne.getFitness() > this->population[0].getFitness())
        {
            this->bestOne = this->population[0];
            
            algorithmTime += timer.stopTimer();

            writter_.writeErrorsRelativeToPopulation(fileName_, populationSize, mutationType, crossoverType, algorithmTime, bestOne.getFitness());
        }

        algorithmTime += timer.stopTimer();
    }

    auto returnPath = new Path(this->bestOne.getFitness(), this->bestOne.getChromosome());

    returnPath->addCityAtFront(this->sourceCity);
    returnPath->addCityAtEnd(this->sourceCity);

    clearVariables();

    return returnPath;
}