#pragma once

#include "EnumCaster.h"

#include <fstream>
#include <iostream>

class FileWritter
{
public:

    FileWritter() = default;
    ~FileWritter();

    void openFile(std::string filePath_);
    void writeIntoFile(std::string algorithm_, size_t instanceSize_, double time_);
    void writeSAIntoFile(std::string fileName_, double stopTime_, double coolingRatio_, double time_, size_t saValue_, size_t bestKnownValue_);
    void writeTBSIntoFile(std::string fileName_, double stopTime_, NeighbourType type_, double time_, size_t tsValue_, size_t bestKnownValue_);
    void writeGAIntoFile(std::string fileName_, MutationType mutType_, double mutProp_, CrossoverType crossType_, double crossProp_, double time_, size_t gaValue_);
    void writeErrorsRelativeToPopulation(std::string fileName_, size_t populationSize_, MutationType mutType_, CrossoverType crossType_, double time_, size_t gaValue_);


private:

    std::string resultsPath;
    std::ofstream resultsFile;
};