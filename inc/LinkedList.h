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

    int getValue() const
    {
        return this->value;
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

    ListElement & operator[](const int & index_);

    void addElement(const int & value_);
    void deleteElement();
};
