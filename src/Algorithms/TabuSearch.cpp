#include "../../inc/Algorithms/TabuSearch.h"

#include <random>

double TabuSearch::stopTime{120};
NeighbourType TabuSearch::neighbourType {NeighbourType::Swap};

Path* TabuSearch::solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_)
{
    // setting up variables 
    setupVariables(matrix_, sourceCity_);

    // // cost is a cost of current path
    size_t cost = this->optimalCost;

    // counter for diversification mechanism
    size_t noBetterSolution{0};

    // main loop
    while((this->time / 1000.0) < stopTime)
    {
        this->timer.startTimer();

        // making move
        makeMove(matrix_, cost);

        // refreshing tabulist ban
        this->tabuList.refreshTimeOut();

        // checking if new cost is better than optimal cost
        if(cost < this->optimalCost)
        {
            this->optimalPath = this->cities;
            this->optimalCost = cost;
            
            // reseting diversification counter
            noBetterSolution = 0;

            this->time += timer.stopTimer();

            continue;
        }

        // diversification mechanism 
        if(noBetterSolution > 9)
        {
            // generating new solution
            randomiseSolution();

            // reseting diversification counter
            noBetterSolution = 0;
            
            this->time += timer.stopTimer();
            
            continue;
        } 

        // increasing diversification counter
        noBetterSolution++;

        this->time += timer.stopTimer();
    }

    // creating path object
    auto returnPath = new Path(this->optimalCost, this->optimalPath);

    // adding source city since its not in the cities vector
    returnPath->addCityAtEnd(this->sourceCity);
    returnPath->addCityAtFront(this->sourceCity);

    // clearing variables
    clearVariables();

    // returning path
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
    // creating variables
    int firstIndex{0}, secondIndex{0}, newCost{0};
    Array<size_t> newCities {this->cities};
    bool better {false};
    size_t noBetterSolutions {0};

    // while solution isnt better or there havent 
    // been better solution
    while(!better && noBetterSolutions < 10)
    {
        // randoming indexes
        while(firstIndex == secondIndex || this->tabuList.isTimedOut(firstIndex, secondIndex))
        {
            firstIndex = RandomGenerator::getInt(0, newCities.size() - 1);
            secondIndex = RandomGenerator::getInt(0, newCities.size() - 1);
        }

        // swapping if first index is smaller
        if(firstIndex > secondIndex)
            std::swap(firstIndex, secondIndex);

        // checking type of move
        // and making a move
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

        // calculating cost
        auto newCost = calculateCost(matrix_, newCities);

        // checking if its better
        if(newCost < cost_)
        {
            this->cities = newCities;
            cost_ = newCost;
            better = true;

            // inserting new entity into tabulist
            this->tabuList.insertNewTabu(firstIndex, secondIndex);
        }
        
        noBetterSolutions++;
    }
    
}

void TabuSearch::clearVariables()
{
    this->citiesNumber = 0;
    optimalCost = INT_MAX;

    this->tabuList.clear();
    this->optimalPath.clear();
    this->cities.clear();

    this->time = 0;
}

