#include "minesweeperGrid.h"
#include <stdlib.h>
#include "config.h"
#include <time.h>
MinesweeperGrid::MinesweeperGrid(int rows, int cols) : Grid(rows, cols)
{
    randomlyPlaceMines();
}
void MinesweeperGrid::randomlyPlaceMines()
{
    srand(time(0));
    for (int i = 0; i < config.mineCount; i++)
    {
        bool done = false;
        while (!done)
        {
            int randomRow = rand() % rows, randomCol = rand() % cols;
            if (doubleArrayGrid[randomRow][randomCol].value != MINE)
            {
                doubleArrayGrid[randomRow][randomCol].value = MINE;
                mineLocations.push_back(Position{randomCol, randomRow});
                done = true;
            }
            else
            {
                done = false;
            }
        }
    }
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {

            if (doubleArrayGrid[r][c].value != MINE)
            {
                int amountOfSurroundingMines = 0;
                if (r - 1 >= 0 && r - 1 < rows && c >= 0 && c < cols && doubleArrayGrid[r - 1][c].value == MINE)
                    amountOfSurroundingMines++;
                if (r - 1 >= 0 && r - 1 < rows && c - 1 >= 0 && c - 1 < cols && doubleArrayGrid[r - 1][c - 1].value == MINE)
                    amountOfSurroundingMines++;
                if (r >= 0 && r < rows && c - 1 >= 0 && c - 1 < cols && doubleArrayGrid[r][c - 1].value == MINE)
                    amountOfSurroundingMines++;
                if (r + 1 >= 0 && r + 1 < rows && c - 1 >= 0 && c - 1 < cols && doubleArrayGrid[r + 1][c - 1].value == MINE)
                    amountOfSurroundingMines++;
                if (r + 1 >= 0 && r + 1 < rows && c >= 0 && c < cols && doubleArrayGrid[r + 1][c].value == MINE)
                    amountOfSurroundingMines++;
                if (r + 1 >= 0 && r + 1 < rows && c + 1 >= 0 && c + 1 < cols && doubleArrayGrid[r + 1][c + 1].value == MINE)
                    amountOfSurroundingMines++;
                if (r >= 0 && r < rows && c + 1 >= 0 && c + 1 < cols && doubleArrayGrid[r][c + 1].value == MINE)
                    amountOfSurroundingMines++;
                if (r - 1 >= 0 && r - 1 < rows && c + 1 >= 0 && c + 1 < cols && doubleArrayGrid[r - 1][c + 1].value == MINE)
                    amountOfSurroundingMines++;
                doubleArrayGrid[r][c].value = (CellValues)(amountOfSurroundingMines + 2);
            }
        }
    }
}
void MinesweeperGrid::reset(int rows, int cols)
{
    this->rows = rows;
    this->rows = cols;
    flagCount = 0;
    mineLocations = {};
    doubleArrayGrid = std::vector<std::vector<Cell>>();
    for (int r = 0; r < rows; r++)
    {
        std::vector<Cell> newRow;
        for (int c = 0; c < cols; c++)
        {

            newRow.push_back(Cell(NIL, this, {c, r}));
        }
        doubleArrayGrid.push_back(newRow);
    }
    drawOffset.x = config.garbage;
    drawOffset.y = config.garbage;
    randomlyPlaceMines();
}