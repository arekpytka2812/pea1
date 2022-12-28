#include "../../inc/Structures/Array.hpp"

template<typename T>
void Array<T>::allocateMemory(size_t newSize_)
{
    if(this->isMemoryAllocated)
        return;

    this->table = new T[newSize_]; 

    this->isMemoryAllocated = true;
    this->tableSize = newSize_;
}

template<typename T>
void Array<T>::deallocateMemory()
{
    if(!isMemoryAllocated)
        return;
    
    delete[] this->table;

    this->table = nullptr;
    this->isMemoryAllocated = false;
    this->tableSize = 0;
}

template<typename T>
bool Array<T>::isInBounds(size_t pos_)
{
    if(pos_ >= 0 && pos_ < this->tableSize)
        return true;

    return false;
}

template<typename T>
void Array<T>::fillUpWithZeros()
{
    for(int i = 0; i < this->tableSize; ++i)
        this->table[i] = 0;
}

template<typename T>
Array<T>::Array(size_t size_)
{
    this->allocateMemory(size_);
    this->fillUpWithZeros();
}

template<typename T>
Array<T>::Array(const Array<T> & origin_)
{
    this->deallocateMemory();
    this->allocateMemory(origin_.size());

    for(int i = 0; i < origin_.size(); ++i)
    {
        this->table[i] = origin_.table[i];
    }
}

template<typename T>
Array<T>::~Array()
{
    this->deallocateMemory();
}

template<typename T>
void Array<T>::reserve(size_t size_)
{
    this->tableSize = size_;

    this->deallocateMemory();
    this->allocateMemory(size_);

    this->fillUpWithZeros();
}

template<typename T>
void Array<T>::operator=(const Array<T> & origin_)
{
    this->deallocateMemory();
    this->allocateMemory(origin_.size());
    
    for(size_t i = 0; i < origin_.size(); ++i)
    {
        this->table[i] = origin_.table[i]; 
    }
}

template<typename T>
T& Array<T>::operator[](size_t index_)
{
    if(this->isInBounds(index_))
        return *(this->table + index_);

    throw new std::out_of_range("You're out of range");
}

template<typename T>
void Array<T>::operator-(const T & value_)
{
    this->erase(value_);
}

template<typename T>
void Array<T>::add(const T & value_, size_t pos_)
{
    if(this->tableSize == 0)
    {
        this->deallocateMemory();
        this->allocateMemory(1);
        this->table[0] = value_;
        return;
    }

    auto tempSize = this->tableSize + 1;
    auto tempTable = new T[tempSize];

    for(int i = 0; i < pos_; ++i)
        tempTable[i] = this->table[i];

    tempTable[pos_] = value_;

    for(int i = pos_ + 1; i < tempSize; ++i)
        tempTable[i] = this->table[i - 1];

    this->deallocateMemory();
    this->allocateMemory(tempSize);
    
    for(int i = 0; i < this->tableSize; ++i)
        this->table[i] = tempTable[i];

    delete[] tempTable;
    tempTable = nullptr;
}

template<typename T>
void Array<T>::addFront(const T & value_)
{
    this->add(value_, 0);
}

template<typename T>
void Array<T>::addEnd(const T & value_)
{
    this->add(value_, this->tableSize);
}

template<typename T>
void Array<T>::erase(const T & value_)
{
    auto tempIndex = this->search(value_);

    if(tempIndex == -1)
        return;

    this->eraseAt(tempIndex);
}

template<typename T>
void Array<T>::eraseAt(size_t pos_)
{
    if(!this->isInBounds(pos_))
        return;

    auto newSize = this->tableSize - 1;

    auto tempTable = new T[newSize];

    for(int i = 0; i < pos_; ++i)
        tempTable[i] = this->table[i];

    for(int i = pos_; i < newSize; ++i)
        tempTable[i] = this->table[i + 1];

    this->deallocateMemory();
    this->allocateMemory(newSize);

    for(int i = 0; i < this->tableSize; ++i)
        this->table[i] = tempTable[i];

    delete[] tempTable;
    tempTable = nullptr;
}

template<typename T>
int Array<T>::search(const T & value_)
{
    auto index = -1;

    for(int i = 0; i < this->tableSize; ++i)
    {
        if(this->table[i] == value_)
        {
            index = i;
        }   
    }    

    return index;
    
}

template<typename T>
void Array<T>::swap(size_t firstIndex_, size_t secondIndex_)
{
    auto temp = this->table[secondIndex_];
    this->table[secondIndex_] = this->table[firstIndex_];
    this->table[firstIndex_] = temp;
}

template<typename T>
void Array<T>::reverse(size_t firstIndex_, size_t secondIndex_)
{
    auto diff = secondIndex_ - firstIndex_;

    if(diff == 0)
        return;

    if(diff == 1)
    {
        this->swap(firstIndex_, secondIndex_);
        return;
    }   

    for(size_t counter = 1; counter < diff; ++firstIndex_, --secondIndex_, ++counter)
    {
        this->swap(firstIndex_, secondIndex_);
    }
    
}

template<typename T>
void Array<T>::insert(size_t firstIndex_, size_t secondIndex_)
{
    T temp = this->table[secondIndex_];

    for(int i = secondIndex_; i > firstIndex_; --i)
    {
        this->table[i] = this->table[i - 1];
    }

    this->table[firstIndex_] = temp;
}

template<typename T>
void Array<T>::printArray()
{
    for(int i = 0; i < this->tableSize; ++i)
    {
        std::cout << "[" << i << "] -> " << this->table[i] << "\n";
    }
}

template<typename T>
void Array<T>::clear()
{
    this->deallocateMemory();
}