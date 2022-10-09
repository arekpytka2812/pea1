#include "../inc/Stack.h"

Stack::~Stack()
{
    while(this->stackSize > 0)
        this->stack->deleteElement();
}

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

void Stack::printStack()
{
    for(int i = 0; i < this->stackSize; ++i)
    {
        std::cout << (*this->stack)[i].getValue() << " -> ";
    }

    std::cout << "\n";
}