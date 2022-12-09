#pragma once

#include "TSPSolver.h"
#include "../Structures/TabuList.h"
#include "../Utils/Timer.h"


class TabuSearch : public TSPSolver
{
    static double stopTime;

    TabuList tabuList;

    size_t citiesNumber{0};
    size_t sourceCity{0};

    size_t optimalCost{INT_MAX};

    Array<size_t> optimalPath;
    Array<size_t> cities;

    Timer timer;
    double time{0};

    void setupVariables(const AdjacencyMatrix & matrix_, size_t sourceCity_) override;
    void randomiseSolution();
    void changeOrder(Array<size_t> & cities_);
    int getRandomInt(int min, int max);
    size_t calculateCost(const AdjacencyMatrix & matrix_, Array<size_t> & cities_);

    void makeMove(Array<size_t> & cities_);
    
    void clearVariables() override;



public:
    
    TabuSearch() = default;
    
    Path* solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_ = 0) override;

    void setStopTime(double stopTime_)
    {
        stopTime = stopTime_;
    }
};