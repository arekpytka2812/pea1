#include "../inc/Array.hpp"

template<typename T>
void Array<T>::allocateMemory(const size_t & newSize_)
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
bool Array<T>::isInBounds(const size_t & pos_)
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
Array<T>::Array(const size_t & size_)
{
    this->allocateMemory(size_);
    this->fillUpWithZeros();
}

template<typename T>
Array<T>::Array(const Array & origin_)
{

}

template<typename T>
Array<T>::~Array()
{
    this->deallocateMemory();
}

template<typename T>
Array<T> & Array<T>::operator=(const Array<T> & origin_)
{

}

template<typename T>
T& Array<T>::operator[](const size_t & index_)
{
    if(this->isInBounds(index_))
        return *(this->table + index_);
}

template<typename T>
void Array<T>::add(const T & value_, const size_t & pos_)
{
    if(this->size == 0)
    {
        this->allocateMemory(1);
        this->table[0] = value_;
        return;
    }

    if(!this->isInBounds(pos_))
        return;

    this->tableSize++;

    auto tempTable = new T[this->tableSize];

    for(int i = 0; i < pos_; ++i)
        tempTable[i] = this->table[i];

    tempTable[pos_] = value_;

    for(int i = pos_ + 1; i < this->tableSize; ++i)
        tempTable[i] = this->table[i - 1];

    this->deallocateMemory();

    this->table = tempTable;
    tempTable = nullptr;
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

    this->erase(tempIndex);
}

template<typename T>
void Array<T>::erase(const size_t & pos_)
{
    if(!this->isInBounds(pos_))
        return;
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
void Array<T>::printArray()
{
    for(int i = 0; i < this->tableSize; ++i)
    {
        std::cout << "[" << i << "] -> " << this->table[i] << "\n";
    }
}