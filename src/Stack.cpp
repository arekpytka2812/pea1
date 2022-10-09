#include "../inc/Stack.h"

void Stack::push(const int & value_)
{
    this->stack->addElement(value_);

    this->stackSize++;
}

void Stack::pop()
{
    this->stack->deleteElement();

    this->stackSize--;
}