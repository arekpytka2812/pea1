#include "../../inc/Utils/CrossoverGenerator.h"

void CrossoverGenerator::pmxCrossover(std::string & chromosome1_, std::string & chromosome2_)
{
    size_t firstIndex{0}, secondIndex{0};

    while(firstIndex == secondIndex)
    {
        firstIndex = RandomGenerator::getInt(0, chromosome1_.size() - 1);
        secondIndex = RandomGenerator::getInt(0, chromosome1_.size() - 1);
    }

    if(firstIndex > secondIndex)
        std::swap(firstIndex, secondIndex);

    std::string buffer1, buffer2;
    buffer1.reserve(chromosome1_.size());
    buffer2.reserve(chromosome2_.size());

    // creating subs to new chromosomes
    auto sub1 = chromosome1_.substr(firstIndex, secondIndex);
    auto sub2 = chromosome2_.substr(firstIndex, secondIndex);

    // inserting from parents
    buffer1.insert(firstIndex, sub2);
    buffer2.insert(firstIndex, sub1);

    // inserting matching genomes
    for(int i = 0; i < chromosome1_.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
            continue;

        if(buffer1.find(chromosome1_[i]))
            continue;

        buffer1[i] = chromosome1_[i];
    }

    for(int i = 0; i < chromosome2_.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
            continue;

        if(buffer2.find(chromosome1_[i]))
            continue;

        buffer2[i] = chromosome2_[i];
    }

    // filling chromosomes
    for(int i = 0; i < chromosome1_.size(); ++i)
    {

    }
}

void CrossoverGenerator::exCrossover(std::string & chromosome1_, std::string & chromosome2_)
{

}