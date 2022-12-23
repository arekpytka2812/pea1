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

    std::cout << "findex: " << firstIndex << " sIndeex: " << secondIndex << "\n";

    std::string buffer1, buffer2;
    
    buffer1.reserve(chromosome1_.size());
    buffer2.reserve(chromosome2_.size());
    buffer1.resize(chromosome1_.size());
    buffer2.resize(chromosome2_.size());

    bool* buf1Contains = new bool[buffer1.size()] {false};
    bool* buf2Contains = new bool[buffer2.size()] {false};


    std::cout << "buff1size: " << buffer1.size() << " buf2siize: " << buffer2.size() << "\n";

    // creating subs to new chromosomes
    auto sub1 = chromosome1_.substr(firstIndex, secondIndex);
    auto sub2 = chromosome2_.substr(firstIndex, secondIndex);

    // inserting from parents
    buffer1.replace(firstIndex, secondIndex, sub2);
    buffer2.replace(firstIndex, secondIndex, sub1);

    // inserting matching genomes
    for(int i = 0; i < chromosome1_.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
        {
            buf1Contains[i] = true;
            continue;
        }
            
        auto found = sub1.find(chromosome1_[i]);
        if(found != std::string::npos)
            continue;

        buffer1[i] = chromosome1_[i];
        buf1Contains[i] = true;
    }

    for(int i = 0; i < chromosome2_.size(); ++i)
    {
        if(i >= firstIndex && i <= secondIndex)
        {
            buf2Contains[i] = true;
            continue; 
        }  

        auto found = sub2.find(chromosome2_[i]); 
        if(found != std::string::npos)
            continue;

        buffer2[i] = chromosome2_[i];
        buf2Contains[i] = true;
    }


    // filling chromosomes
    for(int i = 0, j = 1; i < chromosome1_.size() && j < chromosome1_.size() + 1; ++i)
    {
        if(buf1Contains[i])
            continue;

        while(true)
        {
            auto found = buffer1.find(j);
            if(found != std::string::npos)
            {
                j++;
                continue;
            }

            break;       
        }

        buffer1[i] = j + 48;
        j++;

        buf1Contains[i] = true;
        
    }

    for(int i = 0, j = 1; i < chromosome2_.size() && j < chromosome2_.size() + 1; ++i)
    {
        if(buf2Contains[i])
            continue;

        while(true)
        {
            auto found = buffer2.find(j);
            if(found != std::string::npos)
            {
                j++;
                continue;
            }

            break;       
        }

        buffer2[i] = j + 48;
        j++;

        buf2Contains[i] = true;
        
    }

    std::cout << chromosome1_ << " " << chromosome2_ << "\n" <<  buffer1 << " " << buffer2 << std::endl;

}

void CrossoverGenerator::exCrossover(std::string & chromosome1_, std::string & chromosome2_)
{

}