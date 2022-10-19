#include "main.h"

int main() {

    srand(time(nullptr));

    int data[] = {-1,  81,  50,  18,  75,
                  81,  -1,  76,  21,  37, 
                  50,  76,  -1,  24,  14,
                  18,  21,  24,  -1,  19, 
                  75,  37,  14,  19,  -1};

    auto matrix = new AdjacencyMatrix(5, data);

    auto bf = new BruteForce(5, 0);

    bf->solveTSP(matrix)->printPathInfo();

    return 0;

}
