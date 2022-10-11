#include "../../inc/Algorithms/DP.h"

size_t sourceCity = 0;
size_t currentCity = 1;
AdjacencyMatrix * DP::matrix = nullptr;
Path * DP::resultPath = nullptr;
size_t DP::citiesNumber = 0;
bool * DP::visited = nullptr;
Array<int> * DP::set = nullptr;


Path* DP::solveTSP(AdjacencyMatrix * matrix_)
{
    matrix = matrix_;

    setupVariables();
    findSolution();
}

void DP::setupVariables()
{
    deallocateOldVariables();
    allocateNewVariables();
    initializeSet();
}

void DP::deallocateOldVariables()
{
    delete[] visited;
    delete resultPath;
    delete set;
}

void DP::allocateNewVariables()
{
    citiesNumber = matrix->getCitiesNumber();
    visited = new bool[citiesNumber] {false};
    resultPath = new Path(citiesNumber);
    set = new Array<int>(citiesNumber);
}

void DP::initializeSet()
{
    for(int i = 0; i < citiesNumber; ++i)
    {
        (*set)[i] = i;
    }
}

void DP::findSolution()
{
    visited[sourceCity] = true;
    
    if(set->size() == 2 && sourceCity != currentCity)
    {
        
    }
}

void DP::calculateCost(Array<int> set_, size_t currentCity_)
{
        visited[sourceCity] = true;
    
    if(set->size() == 2 && sourceCity != currentCity)
    {
        
    }
}