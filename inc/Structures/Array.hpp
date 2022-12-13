#pragma once

#include <iostream>


    template<typename T>
    class Array
    {
        T* table {nullptr};
        size_t tableSize{0};

        bool isMemoryAllocated {false};

        void allocateMemory(size_t newSize_);
        void deallocateMemory();
        bool isInBounds(size_t pos_);
        void fillUpWithZeros();

    public:

        Array() = default;
        explicit Array(size_t size_);
        Array(const Array<T> & origin_);
        ~Array();

        void reserve(size_t size_);

        void operator=(const Array<T> & origin_);
        T & operator[](size_t index_);

        void operator-(const T & value_);

        size_t size() const
        {
            return this->tableSize;
        }

        void add(const T & value_, size_t pos_);
        void addFront(const T & value_);
        void addEnd(const T & value_);
        void erase(const T & value_);
        void eraseAt(size_t pos_);

        int search(const T & value_);

        void swap(size_t firstIndex_, size_t secondIndex_);
        void reverse(size_t firstIndex_, size_t secondIndex_);
        void insert(size_t firstIndex_, size_t secondIndex_);
        
        void clear();

        void printArray();
    };
