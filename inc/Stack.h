#include "LinkedList.h"

class Stack
{
    size_t stackSize{0};
    LinkedList* stack;

public:

    Stack() = default;
    explicit Stack(const size_t & stackSize_);

    void push(const int & value_);
    void pop();
    
};