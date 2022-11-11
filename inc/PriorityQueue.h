#include "LinkedList.h"

class PriorityQueue
{
    LinkedList* list{nullptr};

public:

    PriorityQueue();
    ~PriorityQueue();

    void addElement(size_t value_);
    void deleteElement(size_t index_);

    int getFirst() const
    {
        return this->list->operator[](0).getValue();
    }
};