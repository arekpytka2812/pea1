#include "../../inc/Utils/RandomGenerator.h"

#include <random>

int RandomGenerator::getInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

double RandomGenerator::getDouble(double min_, double max_)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min_, max_);

    return dist(gen);
}