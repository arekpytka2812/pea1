#include "../../inc/Structures/TabuList.h"

size_t TabuList::startTimeOut {3};

void TabuList::allocateMemory()
{
    this->tabuList = new size_t*[this->size];

    for(int i = 0; i < this->size; ++i)
    {
        this->tabuList[i] = new size_t[this->size];

        for(int j = 0; j < this->size; ++j)
        {
            if(i == j)
            {
                this->tabuList[i][j] = -1;
                continue;
            }

            this->tabuList[i][j] = 0;
        }
    }
}

void TabuList::deallocateMemory()
{
    for(int i = 0; i < this->size; ++i)
    {
        delete[] this->tabuList[i];
        this->tabuList[i] = nullptr;
    }

    delete[] this->tabuList;
    this->tabuList = nullptr;

    this->size = 0;
}

TabuList::TabuList(const size_t size_)
    :size(size_)
{
    this->allocateMemory();   
}

TabuList::~TabuList()
{
    this->deallocateMemory();
}

void TabuList::insertNewTabu(size_t source_, size_t destination_)
{
    this->tabuList[source_][destination_] = this->startTimeOut;
}

bool TabuList::isTimedOut(size_t source_, size_t destination_)
{
    return this->tabuList[source_][destination_] != 0;
}

void TabuList::refreshTimeOut()
{
    for(int i = 0; i < this->size; ++i)
    {
        for(int j = 0; j < this->size; ++j)
        {
            if(this->tabuList[i][j] == 0)
                continue;

            this->tabuList[i][j]--;
        }
    }
}
