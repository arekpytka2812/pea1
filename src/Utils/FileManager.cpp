#include "../../inc/Utils/FileManager.h" 

void FileManager::setPaths()
{
    auto tempFileName = this->receiveGraphFileName();

    graphPath = tempFileName + ".txt";
    resultsPath = "out/results.csv";

}

std::string FileManager::receiveGraphFileName()
{
    std::string tempFileName;
    std::cout << "Type file name: \n";
    std::cin >> tempFileName;

    return tempFileName;
}

void FileManager::openStreams()
{
    graphFile.open(graphPath.c_str(), std::fstream::in);
    resultsFile.open(resultsPath.c_str(), std::fstream::out | std::fstream::trunc);
}

bool FileManager::checkStreams()
{
    if(graphFile.good() && resultsFile.good())
        return true;
    
    return false;
}

void FileManager::setStreamsPointers()
{
    graphFile.clear();
    graphFile.seekg(0);

    resultsFile.clear();
    resultsFile.seekg(0);
}

void FileManager::closeStreams()
{
    graphFile.close();
    resultsFile.close();
}

void FileManager::clearData()
{
    if(this->data != nullptr)
        delete this->data;
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

FileManager::FileManager()
{
    this->setPaths();
    this->openStreams();

    if(this->checkStreams())
        this->setStreamsPointers();

}

FileManager::~FileManager()
{
    this->closeStreams();
    this->clearData();
}

void FileManager::readGraphFile()
{
    auto tempCitiesNumber = this->receiveCitiesNumber();
    this->clearData();

    this->data = new InsertedData(tempCitiesNumber);

    this->insertValues();
}

void FileManager::writeIntoFile()
{

}

void FileManager::printData()
{
    this->data->printData();
}