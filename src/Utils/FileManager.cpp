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
    std::string buffer;

    for(int i = 0; i < 4; ++i)
        std::getline(this->graphFile, buffer);

    int pos = buffer.find(":");

    size_t citiesNumber = std::stoi(buffer.substr(pos + 1));    

    this->clearData();
    this->data = new InsertedData(citiesNumber);

    for(int i = 3; i < 6; ++i)
        std::getline(this->graphFile, buffer);   

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

void FileManager::readGraphFile(std::string filePath_)
{
    this->graphPath = filePath_;

    this->graphFile.open(graphPath.c_str(), std::fstream::in);

    if(!this->graphFile.good())
    {
        std::cout << "Something went wrong with file\n";
        return;
    }

    this->graphFile.clear();
    this->graphFile.seekg(0);

    readATSP();
}

void FileManager::writeIntoFile(std::string algorithm_, size_t instanceSize_, double time_)
{
    this->resultsFile << algorithm_ << ";" << instanceSize_ << ";" << time_ << "\n";
    this->resultsFile.flush();
}

void FileManager::writeSAIntoFile(std::string fileName_, double stopTime_, double coolingRatio_, double time_, size_t saValue_, size_t bestKnownValue_)
{
    this->resultsFile << fileName_ << ";" << stopTime_ << ";" << coolingRatio_ << ";" << time_ << ";" << saValue_<< ";" << bestKnownValue_ << "\n";
    this->resultsFile.flush();
}

void FileManager::writeTBSIntoFile(std::string fileName_, double stopTime_, NeighbourType type_, double time_, size_t tsValue_, size_t bestKnownValue_)
{
    this->resultsFile << fileName_ << ";" << stopTime_ << ";" << castToString(type_) << ";" << time_ << ";" << tsValue_<< ";" << bestKnownValue_ << "\n";
    this->resultsFile.flush();
}

std::string FileManager::castToString(NeighbourType type_)
{
    switch(type_)
    {
        case NeighbourType::Swap:
            return "swap";
        
        case NeighbourType::Insert:
            return "insert";

        case NeighbourType::Invert:
            return "invert";
    }
}