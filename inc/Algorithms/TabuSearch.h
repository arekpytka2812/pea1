#pragma once

#include <cstddef>

#include "TSPSolver.h"
#include "../Structures/TSEnum.h"
#include "../Structures/TabuList.h"



class TabuSearch : public TSPSolver
{
    

    static double stopTime;

    static NeighbourType neighbourType;
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
    size_t calculateCost(const AdjacencyMatrix & matrix_, Array<size_t> & cities_);

    void makeMove(const AdjacencyMatrix & matrix_, size_t & cost_);
    
    void clearVariables() override;

public:

    
    
    TabuSearch() = default;
    
    Path* solveTSP(const AdjacencyMatrix& matrix_, size_t sourceCity_ = 0) override;

    static void setStopTime(double stopTime_)
    {
        stopTime = stopTime_;
    }

    static void setNeighbourType(enum NeighbourType type_)
    {
        neighbourType = type_;
    }
};