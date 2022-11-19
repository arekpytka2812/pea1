#pragma once

#include <cstddef>
#include <cmath>
#include <iostream>

class ListElement
{
    int value {0};
    ListElement* previous {nullptr};
    ListElement* next {nullptr};

public:
    ListElement() = delete;
    explicit ListElement(int value_);
    ListElement(int value_, ListElement* previous_, ListElement * next_);

    ~ListElement();

    ListElement* getPrevious() const
    {
        return this->previous;
    }

    ListElement* getNext() const
    {
        return this->next;
    }

    int getValue() const
    {
        return this->value;
    }

    void setPrevious(ListElement* previous_)
    {
        this->previous = previous_;
    }

    void setNext(ListElement* next_)
    {
        this->next = next_;
    }
};

class LinkedList
{
    size_t listSize{0};
    ListElement* head{nullptr};
    ListElement* tail{nullptr}; 

public:
    LinkedList() = default;
    ~LinkedList();

    ListElement & operator[](size_t index_);

    void addElement(int value_, size_t index_);
    void addEnd(int value_);

    void deleteFront();
    void deleteElement(size_t index_);
    void deleteEnd();

    void printList();

};
