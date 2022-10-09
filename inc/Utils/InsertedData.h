class InsertedData
{
    size_t citiesNumber {0};
    int* data {nullptr};

public:

    explicit InsertedData(const int & citiesNumber_);
    ~InsertedData();

    void allocateMemory();
    void deallocateMemory();

    int & operator[](const size_t & index_);

    size_t getCitiesNumber() const
    {
        return citiesNumber;
    }

    int* getData() const
    {
        return data;
    }
};