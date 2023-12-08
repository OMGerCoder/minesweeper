#pragma once
#include <vector>
#include "position.h"
class Grid
{
protected:
    int rows;
    int cols;
    std::vector<std::vector<int>> doubleArrayGrid;
public:
    Grid(int rows, int cols);
    int getValue(Position position);
    void setValue(Position position, int newValue);
    void drawGrid(Position position, int cellSize, int spacing);
};
