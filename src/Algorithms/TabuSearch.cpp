#include "../../inc/Algorithms/TabuSearch.h"

#include <random>

double TabuSearch::stopTime{10};
NeighbourType TabuSearch::neighbourType {NeighbourType::Swap};

Path* TabuSearch::solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{

    setupVariables(matrix_, sourceCity_);

    size_t cost = this->optimalCost;
    size_t noBetterSolution{0};

    while((this->time / 1000.0) < stopTime)
    {
        this->timer.startTimer();

        makeMove(matrix_, cost);

        this->tabuList.refreshTimeOut();

        if(cost < this->optimalCost)
        {
            this->optimalPath = this->cities;
            this->optimalCost = cost;
            noBetterSolution = 0;

            continue;
        }

        if(noBetterSolution > 9)
        {
            randomiseSolution();
            noBetterSolution = 0;
            continue;
        } 

        noBetterSolution++;

        this->time += timer.stopTimer();

    }


    auto returnPath = new Path(this->optimalCost, this->optimalPath);

    returnPath->addCityAtEnd(0);
    returnPath->addCityAtFront(0);

    clearVariables();

    return returnPath;
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
    if(this->cities.size() == 0)
    {
        for(int i = 0; i < this->citiesNumber; ++i)
        {
            if(i == this->sourceCity)
                continue;

            this->cities.addEnd(i);
        }
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
    size_t cost{0};

    cost += matrix_.getValue(this->sourceCity, cities_[0]);

    for(size_t i = 0; i < cities_.size() - 1; ++i)
    {
        cost += matrix_.getValue(cities_[i], cities_[i + 1]);
    }

    cost += matrix_.getValue(cities_[cities_.size() - 1], this->sourceCity);

    return cost;
}
    
void TabuSearch::makeMove(const AdjacencyMatrix & matrix_, size_t & cost_)
{
    int firstIndex{0}, secondIndex{0}, newCost{0};
    Array<size_t> newCities = this->cities;
    bool better {false};
    size_t noBetterSolutions {0};

    while(!better && noBetterSolutions < 10)
    {
        while(firstIndex == secondIndex || this->tabuList.isTimedOut(firstIndex, secondIndex))
        {
            firstIndex = RandomGenerator::getInt(0, newCities.size() - 1);
            secondIndex = RandomGenerator::getInt(0, newCities.size() - 1);
        }

        if(firstIndex > secondIndex)
            std::swap(firstIndex, secondIndex);

        switch(neighbourType)
        {
            case NeighbourType::Swap:
                newCities.swap(firstIndex, secondIndex);
                break;

            case NeighbourType::Insert:
                newCities.insert(firstIndex, secondIndex);
                break;

            case NeighbourType::Invert:
                newCities.reverse(firstIndex, secondIndex);
                break;
        }

        auto newCost = calculateCost(matrix_, newCities);

        if(newCost < cost_)
        {
            this->cities = newCities;
            cost_ = newCost;
            better = true;

            this->tabuList.insertNewTabu(firstIndex, secondIndex);
        }
        
        noBetterSolutions++;
    }
    
}

void TabuSearch::clearVariables()
{
    this->tabuList.clear();
    this->optimalPath.clear();
    this->cities.clear();
}

