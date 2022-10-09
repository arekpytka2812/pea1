#include <cstddef>
#include <iostream>

class InsertedData
{
    size_t citiesNumber {0};
    int* data {nullptr};

public:

    explicit InsertedData(const int & citiesNumber_);
    ~InsertedData();

    void allocateMemory();
    void deallocateMemory();

    void printData();

    int & operator[](const size_t & index_);

    size_t getCitiesNumber() const
    {
        return this->citiesNumber;
    }

    int* getData() const
    {
        return this->data;
    }
};