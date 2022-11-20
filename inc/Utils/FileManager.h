#pragma once

#include "InsertedData.h"

#include <fstream>
#include <iostream>
#include <string>

class FileManager
{
    InsertedData *data{nullptr};

    std::string graphPath;
    std::fstream graphFile;

    std::string resultsPath;
    std::fstream resultsFile;

    void openStreams();
    std::string receiveGraphFileName();
    
    void closeStreams();
    void clearData();

    size_t receiveCitiesNumber();
    void insertValues();


public:

    FileManager();
    ~FileManager();

    void readGraphFile();
    void writeIntoFile();

    int* getData() const
    {
        return this->data->getData();
    }

    size_t getCitiesNumber() const 
    {
        return this->data->getCitiesNumber();
    }
};