#include "../inc/LinkedList.h"

ListElement::ListElement(const int & value_)
    : value(value_)
{

}

ListElement::ListElement(const int & value_, ListElement * next_)
    : value(value_), next(next_)
{

}

ListElement::~ListElement()
{
    this->value = 0;
    this->next = nullptr;
}



LinkedList::LinkedList(const size_t & listSize_)
{

}

LinkedList::~LinkedList()
{
    delete[] this->list;
    this->list = nullptr;
    this->listSize = 0;
}

ListElement & LinkedList::operator[](const int & index_)
{
    auto tempPointer = this->list;

    for(int i = 0; i < index_; ++i)
        tempPointer = tempPointer->getNext();

    return *tempPointer;
}

void LinkedList::addElement(const int & value_)
{
    this->list = new ListElement(value_, this->list);

    this->listSize++;
}

void LinkedList::deleteElement()
{
    auto tempPointer = this->list;
    this->list = this->list->getNext();
    delete tempPointer;

    this->listSize--;
}