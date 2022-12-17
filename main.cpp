#include "main.h"

int main() 
{
    srand(time(nullptr));

    // Menu menu;
    // menu.chooseTestsType();


    FileManager fm;
    fm.readGraphFile();

    GraphGenerator gg(12);

    gg.generateData();

    AdjacencyMatrix matrix(fm.getCitiesNumber(), fm.getData());

    auto sa = new SimulatedAnnealing();

    sa->solveTSP(matrix)->printPathInfo();

    auto ts = new TabuSearch();

    ts->solveTSP(matrix)->printPathInfo();





    return 0;

}

