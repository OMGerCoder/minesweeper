#include "cell.h"
#include "config.h"
#include <iostream>
#include <set>
#include "utility.h"
Cell::Cell(CellValues valueIn, Grid *parent, Position locRowCol) : value(valueIn), discovered(false), parent(parent), isFlagged(false)
{
    this->loc.x = locRowCol.x, this->loc.y = locRowCol.y;
    screenLocation.x = config.garbage, screenLocation.y = config.garbage;
}
Cell::~Cell() {}
void Cell::onClick(int mouseX, int mouseY)
{

    if (!isFlagged)
    {
        this->discovered = true;
    }
    int test = 69;
    if (isFlagged)
    {
        return;
    }
    else if (value == MINE)
    {
        UnloadFont(config.font);
        CloseWindow();
        exit(0);
    }
    else if (value == ZERO)
    {
        std::vector<Cell *> cellsToEdit = parent->getSurroundingZeros(loc);
        for (int i = 0; i < cellsToEdit.size(); i++)
        {
            cellsToEdit[i]->discovered = true;
        }
        }
}