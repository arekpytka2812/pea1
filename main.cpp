#include "main.h"

int main() 
{
    srand(time(nullptr));

    // Menu menu;
    // menu.chooseTestsType();

    GraphGenerator gg(9);

    gg.generateData();

    AdjacencyMatrix matrix(gg.getCitiesNumber(), gg.getData());

    auto dp = new DP();

    dp->solveTSP(matrix)->printPathInfo();

    auto sa = new TabuSearch();

    sa->solveTSP(matrix)->printPathInfo();

    return 0;

}

