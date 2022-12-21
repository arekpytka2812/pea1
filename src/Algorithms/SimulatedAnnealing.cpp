#include <random>
#include <cmath>

#include "../../inc/Algorithms/SimulatedAnnealing.h"

double SimulatedAnnealing::coolingRatio {0.999999};
double SimulatedAnnealing::stopTime {10};

Path* SimulatedAnnealing::solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    // setuping up all needed variables
    setupVariables(matrix_, sourceCity_);

    // cost is a cost of current path
    size_t cost = this->optimalCost;

    // temerature that changes during algorithm
    double temperature = startTemperature;

    // main loop
    while((this->time / 1000.0) < stopTime)
    {
        this->timer.startTimer();

        // creating newCities vector based on current path
        Array<size_t> newCities(cities);
        // making move on newCities vector
        changeOrder(newCities);

        // calculating cost of new solution
        size_t newCost = this->calculateCost(matrix_, newCities);

        // calculating delta
        int delta = newCost - cost;

        // if delta is bigger than 0 then
        // algorithm is making decicsion whether 
        // to take solution or not
        if(delta >= 0 && !makeDecision(delta, temperature))
        {
            temperature *= coolingRatio;
            this->time += this->timer.stopTimer();
            continue;
        }

        // changing values
        cost = newCost;
        this->cities = newCities;

        // checking if new cost is better than optimal
        if(cost < this->optimalCost)
        {
            this->optimalCost = cost;
            this->optimalPath = cities;
        }

        // cooling temperature
        temperature *= coolingRatio;
        this->time += this->timer.stopTimer();
    }

    // creating path object
    auto returnPath = new Path(optimalCost, optimalPath);
    
    // adding source city since its not in the cities vector
    returnPath->addCityAtEnd(this->sourceCity);
    returnPath->addCityAtFront(this->sourceCity);

    // clearing variables 
    clearVariables();

    // returning path
    return returnPath;
} 

void SimulatedAnnealing::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;
    this->citiesNumber = matrix_.citiesNumber;

    this->startTemperature = pow(2, this->citiesNumber);

    randomiseSolution();

    this->optimalCost = calculateCost(matrix_, this->cities);

    this->optimalPath = this->cities;
}

void SimulatedAnnealing::randomiseSolution()
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(i == this->sourceCity)
            continue;

        this->cities.addEnd(i);
    }

    for(int i = 0; i < this->citiesNumber; ++i)
        changeOrder(this->cities);
}

void SimulatedAnnealing::changeOrder(Array<size_t> & cities_)
{
    auto firstIndex = RandomGenerator::getInt(0, cities_.size() - 1);
    auto secondIndex = RandomGenerator::getInt(0, cities_.size() - 1);

    cities_.swap(firstIndex, secondIndex);
}

size_t SimulatedAnnealing::calculateCost(const AdjacencyMatrix & matrix_, Array<size_t> & cities_)
{
    size_t cost{0};

    cost += matrix_.getValue(this->sourceCity, cities_[0]);

    for(size_t i = 0; i < cities_.size() - 1; ++i)
    {
        cost += matrix_.getValue(cities_[i], cities_[i + 1]);
    }

    cost += matrix_.getValue(cities_[cities_.size() - 1], this->sourceCity);

    return cost;
}

bool SimulatedAnnealing::makeDecision(const size_t delta_, const double temperature_)
{
    double randPropability = RandomGenerator::getDouble(0.0, 1.0);
    double calculatedPropability = exp(delta_ / temperature_);

    return randPropability < calculatedPropability;
}

void SimulatedAnnealing::clearVariables()
{
    this->citiesNumber = 0;
    optimalCost = INT_MAX;

    this->optimalPath.clear();
    this->cities.clear();
    this->time = 0;
}