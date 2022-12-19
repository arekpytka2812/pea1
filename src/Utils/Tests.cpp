#include "../../inc/Utils/Tests.h"

Tests::Tests()
{
    this->fm = new FileManager();

    this->bf = new BruteForce();
    this->bnb = new BnB();
    this->dp = new DP();
    this->sa = new SimulatedAnnealing();
    this->ts = new TabuSearch();
}

Tests::~Tests()
{
    delete this->fm;

    delete this->bf;
    delete this->bnb;
    delete this->dp;
    delete this->sa;
    delete this->ts;

    if(this->gg != nullptr)
        delete this->gg;

    if(this->matrix != nullptr)
        delete this->matrix;

    if(this->returnPath != nullptr)
        delete this->returnPath;
}

void Tests::performAutoTests()
{
    std::cout << "Processing auto tests...\n";

    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 100; ++j)
        {
            this->generateInstance();

            if(this->returnPath != nullptr)
                delete this->returnPath;

            if(this->instanceSize[this->testCounter] < 13)
                this->testBF();
            
            if(this->returnPath != nullptr)
                delete this->returnPath;

            this->testBnB();

            if(this->returnPath != nullptr)
                delete this->returnPath;

            this->testDP();
            
        }

        this->getAverageDurations();

        this->fm->writeIntoFile("BF", this->instanceSize[this->testCounter], bfDuration);
        this->fm->writeIntoFile("BnB", this->instanceSize[this->testCounter], bnbDuration);
        this->fm->writeIntoFile("DP", this->instanceSize[this->testCounter], dpDuration);
        
        this->testCounter++;

        std::cout << "Test: " << testCounter << "/" << 10 << "\n";

        this->bfDuration = 0;
        this->bnbDuration = 0;
        this->dpDuration = 0;
    }

    std::cout << "Auto tests done!\n";
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
    this->returnPath = bf->solveTSP(*matrix);        
    this->bfDuration += timer.stopTimer();
}

void Tests::testBnB()
{
    timer.startTimer();         
    this->returnPath = bnb->solveTSP(*matrix);        
    this->bnbDuration += timer.stopTimer();
}

void Tests::testDP()
{
    timer.startTimer();         
    this->returnPath = dp->solveTSP(*matrix);        
    this->dpDuration += timer.stopTimer();
}

void Tests::testLocalSearch()
{
    std::string fileNames[] = {"ftv47.atsp", "ftv170.atsp", "rbg403.atsp"};
    int bestKnownValues[] = {1776, 2755, 2465};
    double stopTimes[] = {30.0, 60.0, 90.0};
    double coolingRatios[] = {0.99999, 0.95, 0.9};
    NeighbourType types[] = {NeighbourType::Swap, NeighbourType::Insert, NeighbourType::Invert};

    double saTime {0}, tsTime{0}, saValue{0}, tsValue{0};

    size_t saBestCost {INT_MAX}, tsBestCost{INT_MAX};
    Array<size_t> saBestPath, tsBestPath;

    for(int i = 0; i < 3; ++i)
    {

        if(i == 0)
            continue;

        if(this->matrix != nullptr)
            delete this->matrix;

        fm->readGraphFile(fileNames[i]);

        this->matrix = new AdjacencyMatrix(fm->getCitiesNumber(), fm->getData());

        SimulatedAnnealing::setStopTime(stopTimes[i]);
        TabuSearch::setStopTime(stopTimes[i]);

        for(int j = 0; j < 3; ++j)
        {
            SimulatedAnnealing::setCoolingRatio(coolingRatios[j]);
            TabuSearch::setNeighbourType(types[j]);

            for(int k = 0; k < 10; ++k)
            {
                if(this->returnPath != nullptr)
                    delete this->returnPath;
                
                this->timer.startTimer();
                
                this->returnPath = this->sa->solveTSP(*matrix);

                saTime += this->timer.stopTimer();

                if(this->returnPath->getTotalCost() < saBestCost)
                {
                    saBestPath = this->returnPath->getCities();
                    saBestCost = this->returnPath->getTotalCost();
                }

                saValue += this->returnPath->getTotalCost();

                if(this->returnPath != nullptr)
                    delete this->returnPath;
                
                this->timer.startTimer();
                
                this->returnPath = this->ts->solveTSP(*matrix);

                tsTime += this->timer.stopTimer();

                if(this->returnPath->getTotalCost() < tsBestCost)
                {
                    tsBestPath = this->returnPath->getCities();
                    tsBestCost = this->returnPath->getTotalCost();
                }

                tsValue += this->returnPath->getTotalCost();

            }

            saTime /= 10;
            tsTime /= 10;

            saValue /= 10;
            tsValue /= 10;

            fm->writeSAIntoFile(fileNames[i], stopTimes[i], coolingRatios[j], saTime, saValue, bestKnownValues[i]);
            fm->writeTBSIntoFile(fileNames[i], stopTimes[i], types[j], tsTime, tsValue, bestKnownValues[i]);

            saTime = 0;
            tsTime = 0;
            saValue = 0;
            tsValue = 0;
        }
        
        std::cout << "File: " << i << " done.\n";

    }
}

void Tests::getAverageDurations()
{
    this->bfDuration /= 100;
    this->bnbDuration /= 100;
    this->dpDuration /= 100;
}