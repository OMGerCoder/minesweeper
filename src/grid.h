#pragma once
#include <vector>
#include "position.h"
#include "cell.h"
class Cell;
class Grid
{
private:
    void internalRecursive(Position working, std::vector<Position> *retrievalArray);

protected:
    std::vector<std::vector<Cell>> doubleArrayGrid;
    void randomlyPlaceMines();

public:
    int rows;
    int cols;
    Grid(int rows, int cols);
    Cell *getCell(Position position);
    void setCell(Position position, Cell newCell);
    void drawGrid();
    Position drawOffset;
    Cell *getCellByPositionInArea(Position position);
    std::vector<Cell *> getSurroundingZeros(Position position);
    int flagCount;
    void reset(int rows, int cols);
    std::vector<Position> mineLocations = {};
};
