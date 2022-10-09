#include "InsertedData.h"

#include <fstream>
#include <string>

class FileManager
{
    size_t citiesNumber;
    int *data;

    std::string graphPath;
    std::fstream graphFile;

    std::string resultsPath;
    std::fstream resultsFile;

    void setupStreams();


public:

    FileManager();
    ~FileManager();

    void readData();
    void writeIntoFile();
};