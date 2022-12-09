#include "../../inc/Algorithms/TabuSearch.h"

#include <random>

double TabuSearch::stopTime{120};

Path* TabuSearch::solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{
    setupVariables(matrix_, sourceCity_);

    size_t cost = this->optimalCost;

    while((this->time / 1000.0) < stopTime)
    {
        this->timer.startTimer();

        Array<size_t> newCities(this->cities);
        makeMove(newCities);

        int newCost = calculateCost(matrix_, newCities);

        int delta = newCost - cost;

        if(delta < 0)
        {
            cost = newCost;
            this->cities = newCities;
        }

        if(cost < this->optimalCost)
        {
            this->optimalCost = cost;
            this->optimalPath = this->cities;
        }

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
    auto firstIndex = getRandomInt(0, cities_.size() - 1);
    auto secondIndex = getRandomInt(0, cities_.size() - 1);

    cities_.swap(firstIndex, secondIndex);
}

int TabuSearch::getRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(min, max);

    return dist(gen);
}
    
void TabuSearch::makeMove(Array<size_t> & cities_)
{
    int firstIndex{0}, secondIndex{0};

    do{
        firstIndex = getRandomInt(0, cities_.size() - 1);
        secondIndex = getRandomInt(0, cities_.size() - 1);

    }while(this->tabuList.isTimedOut(firstIndex, secondIndex));

    cities_.swap(firstIndex, secondIndex);
}

