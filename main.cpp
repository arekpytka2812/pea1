#include "main.h"

int main() 
{
    srand(time(nullptr));

    // Menu menu;
    // menu.chooseTestsType();

    GraphGenerator gg(9);

    gg.generateData();

    AdjacencyMatrix matrix(gg.getCitiesNumber(), gg.getData());

    auto sa = new SimulatedAnnealing();

    sa->solveTSP(matrix)->printPathInfo();

    return 0;

}

