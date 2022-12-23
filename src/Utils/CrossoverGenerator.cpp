#include "../../inc/Utils/CrossoverGenerator.h"

void CrossoverGenerator::pmxCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_)
{
    size_t firstIndex{0}, secondIndex{0};

    while(firstIndex == secondIndex)
    {
        firstIndex = RandomGenerator::getInt(0, chromosome1_.size() - 1);
        secondIndex = RandomGenerator::getInt(0, chromosome1_.size() - 1);
    }

    if(firstIndex > secondIndex)
        std::swap(firstIndex, secondIndex);

     
    std::vector<int> buffer1(chromosome1_.size(), -1);
    std::vector<int> buffer2(chromosome2_.size(), -1);  

    // copy genomes into new chromosomes

    copyGenomes(chromosome2_, buffer1, firstIndex, secondIndex);
    copyGenomes(chromosome1_, buffer2, firstIndex, secondIndex);

    // inserting matching genomes
    for(int i = 0; i < buffer1.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
            continue;
            
        auto found = std::find(buffer1.begin(), buffer1.end(), chromosome1_[i]);
        if(found != buffer1.end())
            continue;

        buffer1[i] = chromosome1_[i];
    }

    for(int i = 0; i < buffer2.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
            continue; 

        auto found = std::find(buffer2.begin(), buffer2.end(), chromosome2_[i]); 
        if(found != buffer2.end())
            continue;

        buffer2[i] = chromosome2_[i];
    }

    // filling chromosomes
    for(int i = 0, j = 1; i < chromosome1_.size() && j < chromosome1_.size() + 1; ++i)
    {
        if(buffer1[i] != -1)
            continue;

        while(j < chromosome1_.size())
        {
            auto found = std::find(buffer1.begin(), buffer1.end(), j);
            if(found != buffer1.end())
            {  
                j++;
                continue;
            }

            break;       
        }

        buffer1[i] = j;
        j++;
        
    }

    for(int i = 0, j = 1; i < chromosome2_.size() && j < chromosome2_.size() + 1; ++i)
    {
        if(buffer2[i] != -1)
            continue;

        while(j < chromosome1_.size())
        {
            auto found = std::find(buffer2.begin(), buffer2.end(), j);
            if(found != buffer2.end())
            {
                j++;
                continue;
            }

            break;       
        }

        buffer2[i] = j;
        j++;
    }

    chromosome1_ = buffer1;
    chromosome2_ = buffer2;
}

void CrossoverGenerator::copyGenomes(const std::vector<int> & source_, std::vector<int> & destination_, size_t firstIndex_, size_t secondIndex_)
{
    for(int i = firstIndex_; i <= secondIndex_; ++i)
    {
        destination_[i] = source_[i];
    }
}

void CrossoverGenerator::printVector(const std::vector<int> & vector_)
{
    for(const auto & city: vector_)
    {
        std::cout << city << " ";
    }
}

void CrossoverGenerator::exCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_)
{

}