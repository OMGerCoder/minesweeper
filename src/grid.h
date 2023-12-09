#pragma once
#include <vector>
#include "position.h"
#include "cell.h"
class Cell;
class Grid
{
protected:
    std::vector<std::vector<Cell>> doubleArrayGrid;

public:
    int rows;
    int cols;
    Grid(int rows, int cols);
    Cell getCell(Position position);
    void setCell(Position position, Cell newCell);
    void drawGrid();
    Position drawOffset;
    Cell *getCellByPositionInArea(Position position);
};
