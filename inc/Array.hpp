#pragma once

#include <iostream>

template<typename T>
class Array
{
    T* table {nullptr};
    size_t tableSize{0};

    bool isMemoryAllocated {false};

    void allocateMemory(const size_t & newSize_);
    void deallocateMemory();
    bool isInBounds(const size_t & pos_);
    void fillUpWithZeros();

public:

    Array() = default;
    explicit Array(const size_t & size_);
    Array(const Array & origin_);
    ~Array();

    Array<T> & operator=(const Array<T> & origin_);
    T & operator[](const size_t & index_);

    size_t size() const
    {
        return this->tableSize;
    }

    void add(const T & value_, const size_t & pos_);
    void addEnd(const T & value_);
    void erase(const T & value_);
    void erase(const size_t & pos_);

    int search(const T & value_);

    void printArray();
};