#pragma once

#include <fstream>
#include <string>

#include "InsertedData.h"


class FileReader
{

public:

    FileReader() = default;
    ~FileReader();

    void readFromFile(std::string filePath_);

    size_t getCitiesNumber() const
    {
        return this->dataFromFile->getCitiesNumber();
    }

    int* getData() const 
    {
        return this->dataFromFile->getData();
    }

private:

    void clearDataAndCloseStreamIfNeeded();
    void clearData();

    void setStreamPointers();

    void checkAndReadDiffrentFileFormats();

    void readTSP();
    size_t receiveCitiesNumber();
    void insertValues();

    void readATSP();

    InsertedData * dataFromFile{nullptr};

    std::string filePath;
    std::ifstream graphStream; 

};