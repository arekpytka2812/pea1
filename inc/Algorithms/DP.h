#include "../Path.h"

#include "../Array.hpp"
#include "../../src/Array.tpp"

class DP
{
    static bool * visited;
    static Array<int> set;

    static void setupVariables();

public:
    static Path* solveTSP();

};