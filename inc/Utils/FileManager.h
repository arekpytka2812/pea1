#include "InsertedData.h"

#include <fstream>
#include <iostream>
#include <string>

class FileManager
{
    InsertedData *data;

    std::string graphPath;
    std::fstream graphFile;

    std::string resultsPath;
    std::fstream resultsFile;

    void openStreams();
    std::string receiveGraphFileName();
    void setPaths();
    void setStreamsPointers();
    bool checkStreams();
    
    void closeStreams();
    void clearData();

    size_t receiveCitiesNumber();
    void insertValues();


public:

    FileManager();
    ~FileManager();

    void readGraphFile();
    void writeIntoFile();

    void printData();
};