#pragma once

#include "GraphGenerator.h"
#include "FileManager.h"
#include "Timer.h"

#include "../Algorithms/BruteForce.h"
#include "../Algorithms/DP.h"
#include "../Algorithms/BnB.h"


class Tests
{
    AdjacencyMatrix* matrix {nullptr};
    Path* returnPath {nullptr};

    GraphGenerator* gg {nullptr};
    FileManager *fm{nullptr};
    Timer timer;

    BruteForce* bf {nullptr};
    BnB* bnb {nullptr};
    DP* dp {nullptr};

    double bfDuration{0};
    double bnbDuration{0};
    double dpDuration{0};

    double executionTime{0};
    double maxTime{120000};

    const size_t instanceSize[10] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    size_t testCounter{0};

    void generateInstance();

    void testBF();
    void testBnB();
    void testDP();

    void getAverageDurations();

public:

    Tests();
    ~Tests();

    void performAutoTests();


};