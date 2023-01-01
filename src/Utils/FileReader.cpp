#include "../../inc/Utils/FileReader.h"

FileReader::~FileReader()
{
    this->graphStream.close();
    this->filePath.clear();
    clearData();
}

void FileReader::readFromFile(std::string filePath_)
{
    clearDataAndCloseStreamIfNeeded();

    this->filePath.clear();

    this->filePath = filePath_;

    this->graphStream.open(this->filePath.c_str());

    if(!this->graphStream.good())
    {
        std::cout << "File wasnt opened\n";
        return;
    }

    setStreamPointers();
    
    checkAndReadDiffrentFileFormats();
}

void FileReader::clearDataAndCloseStreamIfNeeded()
{
    clearData();

    if(!this->graphStream.is_open())
        return;

    this->graphStream.close();
}

void FileReader::clearData()
{
    if(this->dataFromFile != nullptr)
        delete this->dataFromFile;
}

void FileReader::setStreamPointers()
{
    this->graphStream.clear();
    this->graphStream.seekg(0);
}

void FileReader::checkAndReadDiffrentFileFormats()
{
    if(this->filePath[this->filePath.size() - 4] == 'a')
        readATSP();
    else   
        readTSP();
}

void FileReader::readTSP()
{
    auto tempCitiesNumber = receiveCitiesNumber();

    this->dataFromFile = new InsertedData(tempCitiesNumber);

    insertValues();
}

size_t FileReader::receiveCitiesNumber()
{
    size_t tempCitiesNumber {0};
    this->graphStream >> tempCitiesNumber;

    return tempCitiesNumber;
}

void FileReader::insertValues()
{
    auto dataSize = this->dataFromFile->getCitiesNumber() * this->dataFromFile->getCitiesNumber(); 

    for(int i = 0; i < dataSize; ++i)
    {
        int tempValue;
        this->graphStream >> tempValue;
        (*this->dataFromFile)[i] = tempValue;
    }
}

void FileReader::readATSP()
{
    std::string buffer;

    for(int i = 0; i < 4; ++i)
        std::getline(this->graphStream, buffer);

    int pos = buffer.find(":");

    size_t citiesNumber = std::stoi(buffer.substr(pos + 1));    

    this->dataFromFile = new InsertedData(citiesNumber);

    for(int i = 3; i < 6; ++i)
        std::getline(this->graphStream, buffer);   

    this->insertValues();
}