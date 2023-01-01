#pragma once

#include "RandomGenerator.h"

#include <vector>
#include <iostream>
#include <algorithm>

class CrossoverGenerator
{
public:

    static void pmxCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_);
  
    static void oxCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_);

static void printVector(const std::vector<int> & vector_);


private:

    static void copyGenomes(const std::vector<int> & source_, std::vector<int> & destination_, size_t firstIndex_, size_t secondIndex_);

    
};