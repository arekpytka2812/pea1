#include "../../inc/Algorithms/BnBsecond.h"

Path* BnBSecond::solveTSP(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->setupVariables(matrix_, sourceCity_);

    this->calculateUpperBound();
    

    this->examineLevel(this->sourceCity, this->startMask, 0, 0);

    return nullptr;
}

void BnBSecond::setupVariables(AdjacencyMatrix* matrix_, size_t sourceCity_)
{
    this->sourceCity = sourceCity_;
    this->copiedMatrix = new AdjacencyMatrix(*matrix_);
    this->citiesNumber = copiedMatrix->citiesNumber;

    this->finalMask = (1 << this->citiesNumber) - 1;
    this->startMask = (1 << this->sourceCity);
}

void BnBSecond::calculateUpperBound()
{
    bool *visited = new bool[this->citiesNumber]{false};

    visited[this->sourceCity] = true;

    size_t currentCity = this->sourceCity;
    this->optimalPath.addEnd(this->sourceCity);

    for(int i = 0; i < this->citiesNumber - 1; ++i)
    {
        auto nextNeighbour = this->findClosestNeighbour(currentCity, visited);

        if(nextNeighbour == -1)
            break;
        
        this->upperBound += this->copiedMatrix->getValue(currentCity, nextNeighbour);
        this->optimalPath.addEnd(nextNeighbour);

        visited[nextNeighbour] = true;
        currentCity = nextNeighbour;
    }

    this->upperBound += this->copiedMatrix->getValue(currentCity, this->sourceCity);
    this->optimalPath.addEnd(this->sourceCity);

    delete[] visited;
}

int BnBSecond::findClosestNeighbour(size_t row_, bool *visited_)
{
    auto min{INT_MAX};
    auto indexOfMin{-1};

    for(size_t i = 0; i < this->citiesNumber; ++i)
    {
        if(visited_[i])
            continue;

        if(this->copiedMatrix->getValue(row_, i) < min && this->copiedMatrix->getValue(row_, i) != -1)
        {
            indexOfMin = i;
            min = this->copiedMatrix->getValue(row_, i);
        }
    }

    return indexOfMin;
}

void BnBSecond::examineLevel(size_t currentCity_, int currentMask_, int lowerBound_, int level)
{
    if(currentMask_ == this->finalMask)
    {
        std::cout << "hmm";

        if(lowerBound_ + this->copiedMatrix->getValue(currentCity_, this->sourceCity) < this->upperBound)
        {
            this->upperBound = lowerBound_ + this->copiedMatrix->getValue(currentCity_, this->sourceCity);
            std::cout << this->upperBound;
            
        }

        std::cout << level  << "kest;" << std::endl;
        return;
    }
    
    PriorityQueue queue;

    this->fillQueue(queue, currentCity_, currentMask_);

    std::cout << std::bitset<8>(currentMask_) << std::endl;

    while(!queue.isEmpty())
    {
        queue.printQueue();

        auto nodeToExamine = &queue.top();
        
        auto currentCity = nodeToExamine->getCity();
        auto cost = nodeToExamine->getCost();

        std::cout << currentCity << std::endl;
        
    
        if(lowerBound_ + cost >= upperBound)
        {
            std::cout << "pomijam " << currentCity << std::endl;
            continue;
        }
            

        this->examineLevel(currentCity, currentMask_ | (1 << currentCity), lowerBound_ + cost, level + 1);
        queue.pop();

        queue.printQueue();
    }

    std::cout << level << "smrodek" << std::endl;

    return;
    
}

void BnBSecond::fillQueue(PriorityQueue & queue_, size_t currentCity_, int currentMask_)
{
    for(int i = 0; i < this->citiesNumber; ++i)
    {
        if(currentMask_ & (1 << i))
            continue;

        queue_.push(i, this->copiedMatrix->getValue(currentCity_, i));
    }
}
