#include "InsertedData.h"

#include <fstream>
#include <filesystem>
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

public:

    FileManager();
    ~FileManager();

    void readData();
    void writeIntoFile();
};