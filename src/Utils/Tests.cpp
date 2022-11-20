#include "../../inc/Utils/Tests.h"

Tests::Tests()
{
    this->fm = new FileManager();

    this->bf = new BruteForce();
    this->bnb = new BnB();
    this->dp = new DP();
}

void Tests::performAutoTests()
{
    for(int i = 0; i < 7; ++i)
    {
        std::cout << this->instanceSize[this->testCounter] << std::endl;
        for(int j = 0; j < 100; ++j)
        {

            this->generateInstance();

            // if(this->returnPath != nullptr)
            //     delete this->returnPath;

            // this->testBF();
            
            if(this->returnPath != nullptr)
                delete this->returnPath;

            this->testBnB();

            if(this->returnPath != nullptr)
                delete this->returnPath;

            this->testDP();
            
        }

        this->getAverageDurations();
        
        std::cout << "BF: " << this->bfDuration << std::endl;
        std::cout << "BnB: " << this->bnbDuration << std::endl;
        std::cout << "DP: " << this->dpDuration << std::endl;
        
        this->testCounter++;

        this->bfDuration = 0;
        this->bnbDuration = 0;
        this->dpDuration = 0;
    }

}

void Tests::generateInstance()
{
    if(this->gg != nullptr)
        delete this->gg;

    if(this->matrix != nullptr)
        delete this->matrix;

    this->gg = new GraphGenerator(this->instanceSize[this->testCounter]);
    this->gg->generateData();

    this->matrix = new AdjacencyMatrix(gg->getCitiesNumber(), gg->getData());
}

void Tests::testBF()
{
    timer.startTimer();         
    this->returnPath = bf->solveTSP(matrix);        
    this->bfDuration += timer.stopTimer();
}

void Tests::testBnB()
{
    timer.startTimer();         
    this->returnPath = bnb->solveTSP(matrix);        
    this->bnbDuration += timer.stopTimer();
}

void Tests::testDP()
{
    timer.startTimer();         
    this->returnPath = dp->solveTSP(matrix);        
    this->dpDuration += timer.stopTimer();
}

void Tests::getAverageDurations()
{
    this->bfDuration /= 100;
    this->bnbDuration /= 100;
    this->dpDuration /= 100;
}