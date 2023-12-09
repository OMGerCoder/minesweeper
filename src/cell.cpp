#include "cell.h"
#include "config.h"
#include <iostream>
#include <set>
Cell::Cell(CellValues valueIn, Grid *parent, Position locRowCol) : value(valueIn), discovered(false), parent(parent)
{
    this->loc.x = locRowCol.x, this->loc.y = locRowCol.y;
    screenLocation.x = config.garbage, screenLocation.y = config.garbage;
}
Cell::~Cell() {}
void Cell::onClick(int mouseX, int mouseY)
{
    if (discovered)
    {
        return; // Skip if already discovered
    }

    discovered = true;
    int test = 69;
    if (value == MINE)
    {
        CloseWindow();
        exit(0);
    }
    else
    {
        if (value == ZERO)
        {
            static std::set<Position> visitedCells;
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    if (dx == 0 && dy == 0)
                        continue; // Skip the current cell
                    int neighborX = loc.x + dx;
                    int neighborY = loc.y + dy;

                    Position neighborCoordinates = {neighborX, neighborY};

                    if (visitedCells.count(neighborCoordinates) > 0)
                    {
                        continue; // Skip visited cells
                    }

                    if (neighborX >= 0 && neighborX < parent->cols &&
                        neighborY >= 0 && neighborY < parent->rows) // Assuming cols and rows are the attributes
                    {
                        visitedCells.insert(neighborCoordinates);

                        if (parent->getCell(neighborCoordinates).value == ZERO)
                        {
                            parent->getCell(neighborCoordinates).onClick(mouseX, mouseY);
                        }
                    }
                }
            }
        }
    }
}