#include "../../inc/Algorithms/TabuSearch.h"

#include <random>

double TabuSearch::stopTime{120};
NeighbourType neighbourType {NeighbourType::Swap};

Path* TabuSearch::solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{
    setupVariables(matrix_, sourceCity_);

    size_t cost = this->optimalCost;

    while((this->time / 1000.0) < stopTime)
    {
        this->timer.startTimer();

      //  Array<size_t> newCities = makeMove(newCities, cost);

        

        this->time += timer.stopTimer();
    }

    auto returnPath = new Path(optimalCost, optimalPath);

    clearVariables();
}

void TabuSearch::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    this->citiesNumber = matrix_.citiesNumber;

    this->tabuList.changeSize(this->citiesNumber);

    randomiseSolution();

    this->optimalCost = this->calculateCost(matrix_, this->cities);

    this->optimalPath = this->cities;
}

void TabuSearch::randomiseSolution()
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

void TabuSearch::changeOrder(Array<size_t> & cities_)
{
    auto firstIndex = RandomGenerator::getInt(0, cities_.size() - 1);
    auto secondIndex = RandomGenerator::getInt(0, cities_.size() - 1);

    cities_.swap(firstIndex, secondIndex);
}

size_t TabuSearch::calculateCost(const AdjacencyMatrix & matrix_, Array<size_t> & cities_)
{

}
    
void TabuSearch::makeMove(const Array<size_t> & cities_, size_t cost_)
{
    int firstIndex{0}, secondIndex{0}, newCost{0};
    Array<size_t> newCities = cities_;

    while(firstIndex == secondIndex)
    {
        firstIndex = RandomGenerator::getInt(0, newCities.size() - 1);
        secondIndex = RandomGenerator::getInt(0, newCities.size() - 1);
    }

    newCities.swap(firstIndex, secondIndex);

    if(this->tabuList.isTimedOut(firstIndex, secondIndex))
    {

    }
    
}

void TabuSearch::clearVariables()
{

}

