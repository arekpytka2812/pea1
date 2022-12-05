#include "../../inc/Utils/FileManager.h" 

FileManager::FileManager()
{
    this->resultsPath = "out/results.csv";
    this->resultsFile.open(resultsPath.c_str(), std::fstream::out | std::fstream::trunc);

    if(!this->resultsFile.good())
    {
        std::cout << "Something went wrong with file\n";
        return;
    } 

    this->resultsFile.clear();
    this->resultsFile.seekg(0);

}

FileManager::~FileManager()
{
    this->closeStreams();
    this->clearData();
}

void FileManager::closeStreams()
{
    this->graphFile.close();
    this->resultsFile.close();
}

void FileManager::clearData()
{
    if(this->data != nullptr)
        delete this->data;
}

void FileManager::readGraphFile()
{
    auto tempFileName = this->receiveGraphFileName();
    this->graphPath = tempFileName;

    this->graphFile.open(graphPath.c_str(), std::fstream::in);

    if(!this->graphFile.good())
    {
        std::cout << "Something went wrong with file\n";
        return;
    }

    this->graphFile.clear();
    this->graphFile.seekg(0);
        
    if(this->graphPath[this->graphPath.size() - 4] == 'a')
        this->readATSP();
    else    
        this->readTSP();

}

void FileManager::readTSP()
{
    auto tempCitiesNumber = this->receiveCitiesNumber();
    this->clearData();

    this->data = new InsertedData(tempCitiesNumber);

    this->insertValues();
}

void FileManager::readATSP()
{
    this->graphFile.seekg(4);

    std::string buffer;

    this->graphFile >> buffer;

    std::cout << buffer << "\n";

    size_t citiesNumber {0};

    this->graphFile >> citiesNumber;

    this->clearData();

    std::cout << citiesNumber;

    this->data = new InsertedData(citiesNumber);

    this->graphFile.seekg(8);

    this->insertValues();
}

std::string FileManager::receiveGraphFileName()
{
    std::string tempFileName;
    std::cout << "Type file name: \n";
    std::cin >> tempFileName;

    return tempFileName;
}

size_t FileManager::receiveCitiesNumber()
{
    size_t tempCitiesNumber {0};

    this->graphFile >> tempCitiesNumber;

    return tempCitiesNumber;
}

void FileManager::insertValues()
{
    auto dataSize = this->data->getCitiesNumber() * this->data->getCitiesNumber(); 

    for(int i = 0; i < dataSize; ++i)
    {
        int tempValue;
        this->graphFile >> tempValue;
        (*this->data)[i] = tempValue;
    }
}

void FileManager::writeIntoFile(std::string algorithm_, size_t instanceSize_, double time_)
{
    this->resultsFile << algorithm_ << ";" << instanceSize_ << ";" << time_ << "\n";
    this->resultsFile.flush();
}