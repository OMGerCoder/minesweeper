#include "grid.h"
#include "position.h"
#include <iostream>
Grid::Grid(int rowsIn, int colsIn) : rows(rowsIn), cols(colsIn) {
    for (int r = 0; r < rows; r++)
    {
        std::vector<int> newRow;
        for (int c = 0; c < cols; c++)
        {
            std::cout << "0 ";

            newRow.push_back(0);
        }
        std::cout << "\n";
        doubleArrayGrid.push_back(newRow);
    }
    
}
// Note that position is in grid cells.
int Grid::getValue(Position position) {
    return doubleArrayGrid[position.y][position.x];
}
void Grid::setValue(Position position, int newValue) {
    doubleArrayGrid[position.y][position.x] = newValue;
}
