#include "../inc/LinkedList.h"

ListElement::ListElement(int value_)
    : value(value_)
{

}

ListElement::ListElement(int value_, ListElement* previous_, ListElement * next_)
    :  value(value_), previous(previous_), next(next_)
{
    if(next_ != nullptr)
        next_ ->setPrevious(this);

    if(previous_ != nullptr)
        previous_ ->setNext(this);
}

ListElement::~ListElement()
{
    this->value = 0;
    this->previous = nullptr;
    this->next = nullptr;
}



LinkedList::~LinkedList()
{
    while(this->listSize > 0)
    {
        this->listSize--;

        if(this->listSize == 0)
        {
            delete this->tail;

            this->head = nullptr;
            this->tail = nullptr;

            return;
        }

        delete this->tail->getPrevious()->getNext();
        
    }
}

ListElement & LinkedList::operator[](size_t index_)
{
    auto middle = ceil((this->listSize + 1) / 2);

    ListElement* tempPointer = nullptr;

    if(index_ > middle)
    {
        tempPointer = this->tail;

        for(int i = this->listSize - 1; i > index_; --i)
        {
            tempPointer = tempPointer->getPrevious();
        }
    }
    else
    {
        tempPointer = this->head;

        for(int i = 0; i < index_; ++i)
        {
            tempPointer = tempPointer->getNext();
        }
    }

    return *tempPointer;

}

void LinkedList::addElement(int value_, size_t index_)
{
    auto tempPrevious = &(*this)[index_ -1];
    auto tempNext = &(*this)[index_];

    auto newElement = new ListElement(value_, tempPrevious, tempNext);

    this->listSize++; 
}

void LinkedList::addEnd(int value_)
{
    if(this->listSize == 0)
    {
        this->tail = new ListElement(value_, nullptr, nullptr);
        this->head = this->tail;
    }
    else
    {
        this->tail = new ListElement(value_, this->tail, nullptr);
    }

    this->listSize++;
}

void LinkedList::deleteFront()
{
    auto tempPointer = this->head;

    this->head = this->head->getNext();
    this->head->setPrevious(nullptr);

    tempPointer->setNext(nullptr);
    delete tempPointer;

    this->listSize--;
}

void LinkedList::printList()
{
    auto current = head;

    for(int i = 0; i < this->listSize; ++i)
    {
        std::cout << current->getValue() << std::endl;

        if(i == this->listSize - 1)
            break; 

        current = current->getNext();
    }

    
}