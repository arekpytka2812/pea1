#pragma once

#include <cstddef>

class TabuList
{
    static size_t startTimeOut;

    size_t** tabuList{nullptr};
    size_t size{0};
    

    void allocateMemory();
    void deallocateMemory();


public:

    TabuList() = default;
    explicit TabuList(const size_t size_);
    ~TabuList();

    void changeSize(const size_t size_);

    void insertNewTabu(size_t source_, size_t destination_);
    bool isTimedOut(size_t source_, size_t destination_);
    void refreshTimeOut();
    void clear();

    static void setTimeOut(size_t timeOut_)
    {
        startTimeOut = timeOut_; 
    }
};