#include "../../inc/Algorithms/SimulatedAnnealing.h"

double SimulatedAnnealing::coolingRatio {0.999};
double SimulatedAnnealing::stopTime {120};
size_t SimulatedAnnealing::startTemperature {0};
size_t SimulatedAnnealing::sourceCity {0};
size_t SimulatedAnnealing::citiesNumber {0};
Array<size_t> SimulatedAnnealing::cities;

Path* SimulatedAnnealing::solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    setupVariables(matrix_, sourceCity_);



    clearVariables();
} 

void SimulatedAnnealing::setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_)
{
    sourceCity = sourceCity_;
    citiesNumber = matrix_.citiesNumber;

    randomiseSolution();
}

void SimulatedAnnealing::randomiseSolution()
{
    for(int i = 0; i < citiesNumber; ++i)
        cities.addEnd(i);

    for(int i = 0; i < citiesNumber; ++i)
        changeOrder();
}

void SimulatedAnnealing::changeOrder()
{
    auto firstIndex = getRandom(0, citiesNumber - 1);
    auto secondIndex = getRandom(0, citiesNumber - 1);

    cities.swap(firstIndex, secondIndex);
}

int SimulatedAnnealing::getRandom(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    return dist(gen);
}

void SimulatedAnnealing::clearVariables()
{

}