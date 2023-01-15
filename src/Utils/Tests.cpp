#include "../../inc/Utils/Tests.h"

Tests::Tests()
{
    this->fileWritter.openFile("out/results.csv");
}

Tests::~Tests()
{

    if(this->matrix != nullptr)
        delete this->matrix;

    if(this->returnPath != nullptr)
        delete this->returnPath;
    
}

void Tests::performAutoTests()
{
    int choice{0};
    while(choice != 4)
    {
        std::cout << "1. Task 1 tests\n2. Task 2 tests\n3. Task 3 tests\n4. Exit\n";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                task1Tests(); 
                break;
        
            case 2:
                task2Tests();
                break;

            case 3:
                task3Tests();

            case 4:
                return;
            
            default:
                break;
        }
    }
}

void Tests::task1Tests()
{
    
    BruteForce bf;
    BnB bnb;
    DP dp;

    GraphGenerator gg;

    const size_t instanceSize[10] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
    size_t testCounter{0};
    
    double bfDuration{0}, bnbDuration{0}, dpDuration{0};

    std::cout << "Processing auto tests...\n";

    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 100; ++j)
        {
            generateInstance(gg, instanceSize[testCounter]);

            if(this->returnPath != nullptr)
                delete this->returnPath;

            if(instanceSize[testCounter] < 13)
            {    
                timer.startTimer();         
                this->returnPath = bf.solveTSP(*matrix);        
                bfDuration += timer.stopTimer();
            }
            
            if(this->returnPath != nullptr)
                delete this->returnPath;

            timer.startTimer();         
            this->returnPath = bnb.solveTSP(*matrix);        
            bnbDuration += timer.stopTimer();

            if(this->returnPath != nullptr)
                delete this->returnPath;

            timer.startTimer();         
            this->returnPath = dp.solveTSP(*matrix);        
            dpDuration += timer.stopTimer();
            
        }

        bfDuration /= 100;
        bnbDuration /= 100;
        dpDuration /= 100;

        this->fileWritter.writeIntoFile("BF", instanceSize[testCounter], bfDuration);
        this->fileWritter.writeIntoFile("BnB", instanceSize[testCounter], bnbDuration);
        this->fileWritter.writeIntoFile("DP", instanceSize[testCounter], dpDuration);
        
        testCounter++;

        std::cout << "Test: " << testCounter << "/" << 10 << "\n";

        bfDuration = 0;
        bnbDuration = 0;
        dpDuration = 0;
    }

    std::cout << "Auto tests done!\n";
}

void Tests::generateInstance(GraphGenerator& gg_, size_t size_)
{

    if(this->matrix != nullptr)
        delete this->matrix;

    gg_.generateData(size_);

    this->matrix = new AdjacencyMatrix(gg_.getCitiesNumber(), gg_.getData());
}


void Tests::task2Tests()
{
    SimulatedAnnealing sa;
    TabuSearch ts;

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
        if(this->matrix != nullptr)
            delete this->matrix;

        fileReader.readFromFile(fileNames[i]);

        this->matrix = new AdjacencyMatrix(fileReader.getCitiesNumber(), fileReader.getData());

        SimulatedAnnealing::setStopTime(stopTimes[i]);
        TabuSearch::setStopTime(stopTimes[i]);

        for(int j = 0; j < 3; ++j)
        {
            SimulatedAnnealing::setCoolingRatio(coolingRatios[j]);
            TabuSearch::setNeighbourType(types[j]);

                if(this->returnPath != nullptr)
                    delete this->returnPath;
                
                this->timer.startTimer();
                
                this->returnPath = sa.solveTSP(fileNames[i], this->fileWritter, *matrix);

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
                
                this->returnPath = ts.solveTSP(fileNames[i], this->fileWritter, *matrix);

                tsTime += this->timer.stopTimer();

                if(this->returnPath->getTotalCost() < tsBestCost)
                {
                    tsBestPath = this->returnPath->getCities();
                    tsBestCost = this->returnPath->getTotalCost();
                }

                tsValue += this->returnPath->getTotalCost();

                std::cout << "File: " << i << ", params: " << j << "\n";

            saTime /= 10;
            tsTime /= 10;

            saValue /= 10;
            tsValue /= 10;

           // fileWritter.writeSAIntoFile(fileNames[i], stopTimes[i], coolingRatios[j], saTime, saValue, bestKnownValues[i]);
           // fileWritter.writeTBSIntoFile(fileNames[i], stopTimes[i], types[j], tsTime, tsValue, bestKnownValues[i]);

            saTime = 0;
            tsTime = 0;
            saValue = 0;
            tsValue = 0;
        }
        
        std::cout << "File: " << i << " done.\n";

    }
}

void Tests::task3Tests()
{
    GeneticAlgorithm ga;

    double stopTimes[] = {30.0, 60.0, 90.0};
    std::string fileNames[] = {"ftv47.atsp", "ftv170.atsp", "rbg403.atsp"};
    int bestKnownValues[] = {1776, 2755, 2465};
    size_t populations[] = {50, 100, 150};

    size_t bestPopulationSize{populations[0]};

    size_t bestCost{INT_MAX};

    CrossoverType crossTypes[] = {CrossoverType::PMX, CrossoverType::OX};
    MutationType mutationTypes[] = {MutationType::Swap, MutationType::Insert}; 

    GeneticAlgorithm::setCrossoverProbability(0.8);
    GeneticAlgorithm::setMutationProbability(0.01);

    for(int i = 0; i < 3; ++i)
    {
        GeneticAlgorithm::setStopTime(stopTimes[i]);
        fileReader.readFromFile(fileNames[i]);

        if(this->matrix != nullptr)
            delete this->matrix;

        this->matrix = new AdjacencyMatrix(fileReader.getCitiesNumber(), fileReader.getData()); 

        for(int j = 0; j < 2; ++j)
        {
            GeneticAlgorithm::setCrossoverType(crossTypes[j]);

            for(int k = 0; k < 2; ++k)
            {
                GeneticAlgorithm::setMutationType(mutationTypes[k]);

                if(this->returnPath != nullptr)
                    delete this->returnPath;

                this->returnPath = ga.solveTSP(1, fileNames[i], fileWritter, *matrix);

            }
        }        
    }


}
