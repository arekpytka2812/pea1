#pragma once

#include "RandomGenerator.h"

#include <string>
#include <iostream>

class CrossoverGenerator
{
public:

    static void pmxCrossover(std::string & chromosome1_, std::string & chromosome2_);
  
    static void exCrossover(std::string & chromosome1_, std::string & chromosome2_);
};