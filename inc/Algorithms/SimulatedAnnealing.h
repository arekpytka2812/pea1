#pragma once

#include <random>

#include "../Structures/Path.h"
#include "../Structures/AdjacencyMatrix.h"

class SimulatedAnnealing
{
    static double coolingRatio;
    static double stopTime;

    static size_t startTemperature;

    static size_t sourceCity;
    static size_t citiesNumber;

    static Array<size_t> cities;

    static void setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity);
    static void randomiseSolution();
    static void changeOrder();
    static int getRandom(int min, int max);

    static int calculateCost(Array<size_t> cities_);

    static void clearVariables();

public:

    static Path* solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity = 0);

    static void setCoolingRatio(double coolingRatio_)
    {
        coolingRatio = coolingRatio_;
    }

    static void setStopTime(double stopTime_)
    {
        stoptime = stoptime_;
    }
};