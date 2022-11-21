#include "../../inc/Utils/Menu.h"

Menu::Menu()
{
    this->bf = new BruteForce();
    this->bnb = new BnB();
    this->dp = new DP();
}

Menu::~Menu()
{
    delete this->fm;

    delete this->bf;
    delete this->bnb;
    delete this->dp;

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

    while(choice != 6)
    {
        std::cout << "1. Read From File\n";
        std::cout << "2. Generate Graph\n"; 
        std::cout << "3. Solve BruteForce\n";
        std::cout << "4. Solve BnB\n";
        std::cout << "5. Solve DP\n";
        std::cout << "6. Exit\n";
        
        std::cin >> choice;

        manualTests();

    }
}


void Menu::manualTests()
{
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

            result = bf->solveTSP(matrix);
            result->printPathInfo();

            break;

        case 4:
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = bnb->solveTSP(matrix);
            result->printPathInfo();

            break;

        case 5: 
            if(matrix == nullptr)
                break;

            if(result != nullptr)
                delete result;

            result = dp->solveTSP(matrix);
            result->printPathInfo();

            break;
            
        case 6:
            return;

        default:
            break;
        }
}