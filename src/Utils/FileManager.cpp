#include "../../inc/Utils/FileManager.h"



void FileManager::setPaths()
{
    auto tempFileName = this->receiveGraphFileName();

    graphPath = "../../" + tempFileName + ".txt";
    resultsPath = "../../out/results.csv";

    std::cout << std::filesystem::path() << std::endl;

    std::cout << graphPath << std::endl;
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

}

FileManager::FileManager()
{
    this->setPaths();
    this->openStreams();

    if(this->checkStreams())
        {this->setStreamsPointers();

        std::cout << "dziala";}
}

FileManager::~FileManager()
{
    this->closeStreams();
}

void FileManager::readData()
{

}

void FileManager::writeIntoFile()
{

}