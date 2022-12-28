#include "../../inc/Utils/Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
    if(this->matrix != nullptr)
        delete this->matrix;

    if(this->result != nullptr)
        delete this->result;
}

void Menu::chooseTestsType()
{
    while(true)
    {
        std::cout << "1. Task 1 Manual Tests\n";
        std::cout << "2. Task 2 Manual Tests\n";
        std::cout << "3. Task 3 Manual Tests\n";
        std::cout << "4. Auto Tests\n";
        std::cout << "5. Exit\n";

        std::cin >> choice;

        switch(choice)
        {
            case 1: 
                task1Menu();
                break;

            case 2:
                task2Menu();
                break;
            
            case 3:
                task3Menu();
                break;

            case 4:
                autoTests.performAutoTests();
                break;

            case 5:
                exit(0);

            default:
                break;
        }
    }
}

void Menu::task1Menu()
{

    while(choice != 6)
    {
        std::cout << "1. Read From File\n";
        std::cout << "2. Generate Graph\n"; 
        std::cout << "3. Solve BruteForce\n";
        std::cout << "4. Solve BnB\n";
        std::cout << "5. Solve DP\n";
        std::cout << "6. Exit\n";

        std::cin >> choice;

        task1ManualTests();
    }

    choice = 0;
}

void Menu::task1ManualTests()
{
    std::string filePath;
    size_t howMany;

    BruteForce bf;
    BnB bnb;
    DP dp;

    switch(choice)
    {
        case 1:
            if(matrix != nullptr)
                delete matrix;

            std::cout << "Type file name:\n";
            std::cin >> filePath;

            fileReader.readFromFile(filePath); 

            matrix = new AdjacencyMatrix(fileReader.getCitiesNumber(), fileReader.getData());

            break;

        case 2:
            if(matrix != nullptr)
                delete matrix;

            std::cout << "How many cities?\n";
            std::cin >> howMany;

            gg.generateData(howMany);

            matrix = new AdjacencyMatrix(gg.getCitiesNumber(), gg.getData());

            break;

        case 3:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            timer.startTimer();
            result = bf.solveTSP(*matrix);
            duration = timer.stopTimer();

            result->printPathInfo();
            
            std::cout << "Duration: " << duration / 1000.0 << " s\n";

            break;

        case 4:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            timer.startTimer();
            result = bnb.solveTSP(*matrix);
            duration = timer.stopTimer();

            result->printPathInfo();
            
            std::cout << "Duration: " << duration / 1000.0 << " s\n";

            break;

        case 5: 
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            timer.startTimer();
            result = dp.solveTSP(*matrix);
            duration = timer.stopTimer();

            result->printPathInfo();
            
            std::cout << "Duration: " << duration / 1000.0 << " s\n";

            break;

    }
}

void Menu::task2Menu()
{
    while(choice != 7)
    {
        std::cout << "1. Read From File\n";
        std::cout << "2. Set stop time for SA and TS\n";
        std::cout << "3. Choose neighbour type for TS\n";
        std::cout << "4. Solve TS\n";
        std::cout << "5. Set cooling ratio for SA\n";
        std::cout << "6. Solve SA\n";
        std::cout << "7. Exit\n";

        std::cin >> choice;

        task2ManualTests();
    }

    choice = 0;
}

void Menu::task2ManualTests()
{
    std::string filePath;
    double stopTime{0.0};

    TabuSearch ts;
    SimulatedAnnealing sa;

    switch(choice)
    {
        case 1:
            if(matrix != nullptr)
                delete matrix;

            std::cout << "Type file name:\n";
            std::cin >> filePath;

            fileReader.readFromFile(filePath); 

            matrix = new AdjacencyMatrix(fileReader.getCitiesNumber(), fileReader.getData());

            break;


        case 2:
            std::cout << "Type stop time in seconds:\n";
            std::cin >> stopTime;

            SimulatedAnnealing::setStopTime(stopTime);
            TabuSearch::setStopTime(stopTime);
            break;

        case 3:
            setNeighbourType();
            break;

        case 4:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = ts.solveTSP(*matrix);

            result->printPathInfo();
            break;

        case 5:
            setCoolingRatio();
            break;

        case 6:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = sa.solveTSP(*matrix);

            result->printPathInfo();
            break;

        case 7:
            return;

        default:
            break;
    }
}

void Menu::setNeighbourType()
{
    NeighbourType type = NeighbourType::Swap;
    int choice{-1};

    while(choice < 1 || choice > 3)
    {   
        std::cout << "Choose type:\n1. Swap\n2. Insert\n3. Invert\n";
        std::cin >> choice;
    }

    switch (choice)
    {
        case 1:
            type = NeighbourType::Swap;
            break;

        case 2:
            type = NeighbourType::Insert;
            break;

        case 3:
            type = NeighbourType::Invert;
            break;
    }

    TabuSearch::setNeighbourType(type);

}

void Menu::setCoolingRatio()
{
    double ratio{-1};

    while(ratio < 0.0 || ratio > 1.0)
    {   
        std::cout << "Type cooling ratio (0.0 - 1.0):\n";
        std::cin >> ratio;
    }

    SimulatedAnnealing::setCoolingRatio(ratio);

}

void Menu::task3Menu()
{
    while(choice != 10)
    {
        std::cout << "1. Read from file\n";
        std::cout << "2. Print graph\n";
        std::cout << "3. Set stop time for GA\n";
        std::cout << "4. Set start population size\n";
        std::cout << "5. Set mutation propability\n";
        std::cout << "6. Set crossover propability\n";
        std::cout << "7. Set crossover method\n";
        std::cout << "8. Set mutation method\n";
        std::cout << "9. Solve Genetic Algorithm\n";
        std::cout << "10. Exit\n";

        std::cin >> choice;

        task3ManualTests();
    }

    choice = 0;
}

void Menu::task3ManualTests()
{
    std::string filePath;
    double stopTime{0.0}, mutationPropability{0.0}, crossoverPropability{0.0};
    size_t populationSize{0};

    GeneticAlgorithm ga;

    switch(choice)
    {
        case 1:
            if(matrix != nullptr)
                delete matrix;

            std::cout << "Type file name:\n";
            std::cin >> filePath;

            fileReader.readFromFile(filePath); 

            matrix = new AdjacencyMatrix(fileReader.getCitiesNumber(), fileReader.getData());

            break;

        case 2:

            if(matrix == nullptr)
                break;

            matrix->printMatrix();

            break;

        case 3:
            std::cout << "Type stop time in seconds:\n";
            std::cin >> stopTime;

            GeneticAlgorithm::setStopTime(stopTime);
            break;

        case 4:
            std::cout << "Type population size:\n";
            std::cin >> populationSize;

            GeneticAlgorithm::setPopulationSize(populationSize);
            break;

        case 5:
            std::cout << "Type mutation propability:\n";
            std::cin >> mutationPropability;

            GeneticAlgorithm::setMutationProbability(mutationPropability);
            break;

        case 6:
            std::cout << "Type crossover propability:\n";
            std::cin >> crossoverPropability;

            GeneticAlgorithm::setCrossoverProbability(crossoverPropability);
            break;

        case 7:
            setCrossoverType();
            break;

        case 8:
            setMutationType();
            break;
        
        case 9:
            
            if(this->result != nullptr)
                delete this->result;

            if(this->matrix == nullptr)
                break;
            
            result = ga.solveTSP(*matrix);

            result->printPathInfo();

            break;

        case 10:
            return;

        default:
            break;

    }
}

void Menu::setCrossoverType()
{
    CrossoverType type = CrossoverType::PMX;
    int choice{-1};

    while(choice < 1 || choice > 2)
    {   
        std::cout << "Choose type:\n1. PMX\n2. OX\n";
        std::cin >> choice;
    }

    switch (choice)
    {
        case 1:
            type = CrossoverType::PMX;
            break;

        case 2:
            type = CrossoverType::OX;
            break;

        default:
            break;
    }

    GeneticAlgorithm::setCrossoverType(type);  
}

void Menu::setMutationType()
{
    MutationType type = MutationType::Swap;
    int choice{-1};

    while(choice < 1 || choice > 2)
    {   
        std::cout << "Choose type:\n1. Swap\n2. Insert\n";
        std::cin >> choice;
    }

    switch (choice)
    {
        case 1:
            type = MutationType::Swap;
            break;

        case 2:
            type = MutationType::Insert;
            break;

        default:
            break;
    }

    GeneticAlgorithm::setMutationType(type);  
}