#include "../../inc/Utils/CrossoverGenerator.h"

void CrossoverGenerator::pmxCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_)
{
    auto firstIndex{RandomGenerator::getInt(0, chromosome1_.size() - 2)};
    auto secondIndex{RandomGenerator::getInt(firstIndex + 1, chromosome1_.size() - 1)};
     
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

void CrossoverGenerator::oxCrossover(std::vector<int> & chromosome1_, std::vector<int> & chromosome2_)
{
    auto firstIndex{RandomGenerator::getInt(0, chromosome1_.size() - 2)};
    auto secondIndex{RandomGenerator::getInt(firstIndex + 1, chromosome1_.size() - 1)};

    std::vector<int> buffer1(chromosome1_.size(), -1);
    std::vector<int> buffer2(chromosome2_.size(), -1);

    copyGenomes(chromosome2_, buffer1, firstIndex, secondIndex);
    copyGenomes(chromosome1_, buffer2, firstIndex, secondIndex);
    
    int parentIndex =  (secondIndex + 1) % buffer1.size(), childIndex = (secondIndex + 1) % buffer1.size();

    while(std::find(buffer1.begin(), buffer1.end(), -1) != buffer1.end())
    {
        auto found = std::find(buffer1.begin(), buffer1.end(), chromosome1_[parentIndex]);

        if(found != buffer1.end())
        {
            parentIndex = (++parentIndex) % buffer1.size();
            continue;
        }

        buffer1[childIndex] = chromosome1_[parentIndex];

        parentIndex = (++parentIndex) % buffer1.size();
        childIndex = (++childIndex) % buffer1.size();
    }

    parentIndex = (secondIndex + 1) % buffer2.size();

    childIndex = (secondIndex + 1) % buffer2.size();

    while(std::find(buffer2.begin(), buffer2.end(), -1) != buffer2.end())
    {
        auto found = std::find(buffer2.begin(), buffer2.end(), chromosome2_[parentIndex]);

        if(found != buffer2.end())
        {
            parentIndex = (++parentIndex) % buffer2.size();
            continue;
        }

        buffer2[childIndex] = chromosome2_[parentIndex];

        parentIndex = (++parentIndex) % buffer2.size();
        childIndex = (++childIndex) % buffer2.size();
    }

    chromosome1_ = buffer1;
    chromosome2_ = buffer2;
}