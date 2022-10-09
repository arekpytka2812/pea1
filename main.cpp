#include "main.h"

int main() {

    srand(time(nullptr));

    int data[] = {-1,  81,  50,  18,  75,
                  81,  -1,  76,  21,  37, 
                  50,  76,  -1,  24,  14,
                  18,  21,  24,  -1,  19, 
                  75,  37,  14,  19,  -1};

    auto gg = new GraphGenerator(5);
    gg->generateData();

    std::cout << "\n";

    auto matrix = new AdjacencyMatrix(gg->getCitiesNumber(), gg->getData());

    matrix->printMatrix();


    return 0;
}
