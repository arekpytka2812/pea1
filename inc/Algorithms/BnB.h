#pragma once

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
    void reduceColumns();

    bool isZeroInColumn(size_t column_);

    int findMinInColumn(size_t column_);
    int findMinInRow(size_t row_);


public:

    Path* solveTSP(AdjacencyMatrix* matrix_);
};
