#pragma once

#include "TSPSolver.h"

#include "../Utils/FileWritter.h"

class SimulatedAnnealing : public TSPSolver
{
    static double coolingRatio;
    static double stopTime;

    size_t startTemperature{1000};

    size_t sourceCity{0};
    size_t citiesNumber{0};

    size_t optimalCost{INT_MAX}; 
    Array<size_t> optimalPath;

    Array<size_t> cities;

    double time{0};

    Timer timer;

    FileWritter flieWritter;

    void setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity) override;
    void randomiseSolution();
    void changeOrder(Array<size_t> & cities_);

    size_t calculateCost(const AdjacencyMatrix & matrix_, Array<size_t> & cities_);

    bool makeDecision(const size_t delta_, const double temperature_);

    void clearVariables() override;

public:

    Path* solveTSP(const AdjacencyMatrix & matrix_, size_t sourceCity = 0) override;

    Path* solveTSP(std::string fileName, FileWritter & writter, const AdjacencyMatrix & matrix_, size_t sourceCity = 0);

    static void setCoolingRatio(double coolingRatio_)
    {
        coolingRatio = coolingRatio_;
    }

    static void setStopTime(double stopTime_)
    {
        stopTime = stopTime_;
    }
};