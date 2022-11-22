#pragma once

#include "Tests.h"

class Menu
{
    Tests autoTests;
    Timer timer;

    int choice {0};
    size_t howMany {0};
    double duration{0};

    FileManager* fm {nullptr};
    GraphGenerator* gg {nullptr};
    AdjacencyMatrix* matrix {nullptr};
    BruteForce* bf {nullptr};
    DP* dp {nullptr};
    Path* result {nullptr};
    BnB* bnb {nullptr};

    void manualTests();
    void manualMainMenu();

public:

    Menu();
    ~Menu();

    void chooseTestsType();
};