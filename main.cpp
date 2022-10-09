#include "main.h"

int main() {

    srand(time(nullptr));

    int data[] = {-1,  81,  50,  18,  75,
                  81,  -1,  76,  21,  37, 
                  50,  76,  -1,  24,  14,
                  18,  21,  24,  -1,  19, 
                  75,  37,  14,  19,  -1};

    auto stack = new Stack();

    int i = 1;

    while(i < 7)
    {
        stack->push(i);
        ++i;
    }

    stack->printStack();

    while(i > 5)
    {
        stack->pop();
        --i;
    }

    stack->printStack();


    return 0;
}
