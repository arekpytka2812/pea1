#pragma once

#include <string>

class CrossoverGenerator
{
public:

    static void pmxCrossover(std::string & chromosome1_, std::string & chromosome2_);
    static void exCrossover(std::string & chromosome1_, std::string & chromosome2_);
};