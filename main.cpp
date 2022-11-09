#include "main.h"

    int choice = 0;
    size_t howMany = 0;

    FileManager* fm = nullptr;
    GraphGenerator* gg = nullptr;
    AdjacencyMatrix* matrix = nullptr;
    BruteForce* bf = nullptr;
    DP* dp = nullptr;
    Path* result = nullptr;

void menuActions();

int main() 
{

    srand(time(nullptr));

    int data[] = {-1,  20,  30,  31,  28,  4,
                  30,  -1,  10,   4,  20, 44, 
                  40,  20,  -1,  10,  22, 50,
                  41,   4,  20,  -1,  14, 42,
                  38,  30,  32,   4,  -1, 28,
                  50,   4,  60,  52,  38, -1};

    bf = new BruteForce();
    dp = new DP();

    

    while(choice != 5)
    {
        std::cout << "1. Read From File\n";
        std::cout << "2. Generate Graph\n"; 
        std::cout << "3. Solve BruteForce\n";
        std::cout << "4. Solve DP\n";
        std::cout << "5. Exit\n";
        
        std::cin >> choice;

        menuActions();

    }




    return 0;

}

void menuActions()
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

            result = dp->solveTSP(matrix);
            result->printPathInfo();

            break;
            
        case 5:
            exit(0);
        }
}