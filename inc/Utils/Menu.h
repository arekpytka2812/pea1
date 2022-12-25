#pragma once

#include "Tests.h"

class Menu
{
public:

    Menu();
    ~Menu();

    void chooseTestsType();

private:
    Tests autoTests;
    Timer timer;

    int choice {0};
    double duration{0};

    FileReader fileReader;

    GraphGenerator gg;
    AdjacencyMatrix* matrix {nullptr};
    Path* result {nullptr};
    
    void task1Menu();
    void task1ManualTests();
    
    void task2Menu();
    void task2ManualTests();

    void setNeighbourType();
    void setCoolingRatio();

    void task3Menu();
    void task3ManualTests();

    void setCrossoverType();
    void setMutationType();

    void manualTests();
    void manualMainMenu();

    


};