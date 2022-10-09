#include <cstddef>

class ListElement
{
    int value {0};
    ListElement* next {nullptr};

public:
    ListElement() = delete;
    explicit ListElement(const int & value_);
    ListElement(const int & value_, ListElement * next_);

    ~ListElement();

    ListElement* getNext() const
    {
        return this->next;
    }
};

class LinkedList
{
    size_t listSize{0};
    ListElement* list{nullptr}; 

public:
    LinkedList() = default;
    LinkedList(const size_t & listSize_);
    ~LinkedList();

    void addElement(const int & value_);
    void deleteElement();
};
