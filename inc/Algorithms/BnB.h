#include "../AdjacencyMatrix.h"
#include "../Path.h"

class BnB
{
    AdjacencyMatrix *copiedMatrix {nullptr};
    size_t citiesNumber{0};

    size_t minimumCost{0};

    void setupVariables(AdjacencyMatrix* matrix_);
    void reduceMatrix();
    void reduceRows();

    bool isZeroInRow(const size_t & row_);

    int findMinInColumn(const size_t & column_);
    int findMinInRow(const size_t & row_);


public:

    Path* solveTSP(AdjacencyMatrix* matrix_);
};