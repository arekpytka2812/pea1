#include "main.h"

int main() {

    srand(time(nullptr));

    int data[] = {-1,  81,  50,  18,  75,
                  81,  -1,  76,  21,  37, 
                  50,  76,  -1,  24,  14,
                  18,  21,  24,  -1,  19, 
                  75,  37,  14,  19,  -1};

    auto array = new Array<int>(5);

    (*array)[2] = 5;

    array->printArray();

    auto matrix = new AdjacencyMatrix(5, data);

    std::cout << matrix->getValue(0, 3);


    return 0;
}
