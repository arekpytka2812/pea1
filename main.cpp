#include "main.h"

int main() 
{
    srand(time(nullptr));

    // Menu menu;
    // menu.chooseTestsType();


    FileReader fr;

    fr.readFromFile("tsp_6_2.txt");

    AdjacencyMatrix matrix(fr.getCitiesNumber(), fr.getData());

    // BruteForce bf;

    // bf.solveTSP(matrix)->printPathInfo();

    GeneticAlgorithm ga;

    ga.solveTSP(matrix)->printPathInfo();

    return 0;

}

