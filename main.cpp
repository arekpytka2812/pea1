#include "main.h"

int main() 
{
    srand(time(nullptr));

    // Menu menu;
    // menu.chooseTestsType();

    GraphGenerator gg(9);

    gg.generateData();

    AdjacencyMatrix matrix(gg.getCitiesNumber(), gg.getData());

    SimulatedAnnealing::solveTSP(matrix);

    return 0;

}

