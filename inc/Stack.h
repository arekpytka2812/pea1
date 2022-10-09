#include "LinkedList.h"

#include <iostream>

class Stack
{
    size_t stackSize{0};
    LinkedList* stack;

public:

    Stack();
    explicit Stack(const size_t & stackSize_);
    ~Stack();

    void push(const int & value_);
    void pop();

    void printStack();
};