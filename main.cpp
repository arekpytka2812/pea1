#include "main.h"

int main() 
{

    srand(time(nullptr));

    int data[] = {-1,  20,  30,  31,  28,  4,
                  30,  -1,  10,   4,  20, 44, 
                  40,  20,  -1,  10,  22, 50,
                  41,   4,  20,  -1,  14, 42,
                  38,  30,  32,   4,  -1, 28,
                  50,   4,  60,  52,  38, -1};


    auto fm = new FileManager();
    fm->readGraphFile();

    auto matrix = new AdjacencyMatrix(fm->getCitiesNumber(), fm->getData());

    matrix->printMatrix();

    auto dp = new DP();

    dp->solveTSP(matrix)->printPathInfo();

    auto bf = new BruteForce();

    bf->solveTSP(matrix)->printPathInfo();

    return 0;

}
