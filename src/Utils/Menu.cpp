#include "../../inc/Utils/Menu.h"

Menu::Menu()
{
    this->bf = new BruteForce();
    this->bnb = new BnB();
    this->dp = new DP();
    this->sa = new SimulatedAnnealing();
    this->ts = new TabuSearch();
}

Menu::~Menu()
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

}

void Menu::chooseTestsType()
{
    while(true)
    {
        std::cout << "1. Manual Tests\n";
        std::cout << "2. Auto Tests\n";
        std::cout << "3. Exit\n";

        std::cin >> choice;

        switch(choice)
        {
            case 1: 
                manualMainMenu();
                break;

            case 2:
                autoTests.performAutoTests();
                break;

            case 3:
                exit(0);
                break;

            default:
                break;
        }
    }
}

void Menu::manualMainMenu()
{

    while(choice != 11)
    {
        std::cout << "1. Read From File\n";
        std::cout << "2. Generate Graph\n";
        std::cout << "---- Task 1 algorithms ----\n"; 
        std::cout << "3. Solve BruteForce\n";
        std::cout << "4. Solve BnB\n";
        std::cout << "5. Solve DP\n";
        std::cout << "---- Task 2 algorithms ----\n";
        std::cout << "6. Set stop time for SA and TS\n";
        std::cout << "7. Choose neighbour type for TS\n";
        std::cout << "8. Solve TS\n";
        std::cout << "9. Set cooling ratio for SA\n";
        std::cout << "10. Solve SA\n";
        std::cout << "11. Exit\n";
        
        std::cin >> choice;

        manualTests();

    }
}


void Menu::manualTests()
{
    double stopTime{0};

    switch (choice)
    {
        case 1:
            if(fm != nullptr)
                delete fm;
            
            if(matrix != nullptr)
                delete matrix;
            
            fm = new FileManager();
            fm->readGraphFile(); 

            matrix = new AdjacencyMatrix(fm->getCitiesNumber(), fm->getData());

            break;
        
        case 2:
            if(gg != nullptr)
                delete gg;
            
            if(matrix != nullptr)
                delete matrix;

            std::cout << "How many cities?\n";
            std::cin >> howMany;

            gg = new GraphGenerator(howMany);
            gg->generateData();

            matrix = new AdjacencyMatrix(gg->getCitiesNumber(), gg->getData());

            break;

        case 3:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            timer.startTimer();
            result = bf->solveTSP(*matrix);
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
            result = bnb->solveTSP(*matrix);
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
            result = dp->solveTSP(*matrix);
            duration = timer.stopTimer();

            result->printPathInfo();
            
            std::cout << "Duration: " << duration / 1000.0 << " s\n";

            break;
            
        case 6:
            std::cout << "Type stop time in seconds:\n";
            std::cin >> stopTime;

            SimulatedAnnealing::setStopTime(stopTime);
            TabuSearch::setStopTime(stopTime);
            break;

        case 7:
            setNeighbourType();
            break;

        case 8:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = this->ts->solveTSP(*matrix);

            result->printPathInfo();
            break;

        case 9:
            setCoolingRatio();
            break;

        case 10:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = this->sa->solveTSP(*matrix);

            result->printPathInfo();
            break;

        case 11:
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