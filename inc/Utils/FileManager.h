#pragma once

#include "InsertedData.h"
#include "../Structures/TSEnum.h"


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

    void readTSP();
    void readATSP();

    std::string castToString(NeighbourType type_);

public:

    FileManager();
    ~FileManager();

    void readGraphFile();
    void readGraphFile(std::string filePath_);
    void writeIntoFile(std::string algorithm_, size_t instanceSize_, double time_);
    void writeSAIntoFile(std::string fileName_, double stopTime_, double coolingRatio_, double time_, size_t saValue_, size_t bestKnownValue_);
    void writeTBSIntoFile(std::string fileName_, double stopTime_, NeighbourType type_, double time_, size_t tsValue_, size_t bestKnownValue_);


    int* getData() const
    {
        return this->data->getData();
    }

    size_t getCitiesNumber() const 
    {
        return this->data->getCitiesNumber();
    }
};