#include "grid.h"
#include "position.h"
#include <iostream>
#include <raylib.h>
#include "config.h"
#include "utility.h"
Grid::Grid(int rowsIn, int colsIn) : rows(rowsIn), cols(colsIn)
{
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
    flagCount = 0;
}
// Note that position is in grid cells.
Cell *Grid::getCell(Position position)
{
    return &doubleArrayGrid[position.y][position.x];
}
void Grid::setCell(Position position, Cell newValue)
{
    doubleArrayGrid[position.y][position.x] = newValue;
}
void Grid::drawGrid()
{
    Position currentPosition = drawOffset;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (doubleArrayGrid[r][c].value == MINE && doubleArrayGrid[r][c].discovered)
            {
                DrawRectangle(currentPosition.x, currentPosition.y, config.cellSize, config.cellSize, config.cellColors[MINE]);
            }
            else if (doubleArrayGrid[r][c].isFlagged)
            {
                DrawRectangle(currentPosition.x, currentPosition.y, config.cellSize, config.cellSize, RED);
            }
            else if (doubleArrayGrid[r][c].discovered)
            {
                DrawRectangle(currentPosition.x, currentPosition.y, config.cellSize, config.cellSize, config.cellColors[NIL]);
                switch (doubleArrayGrid[r][c].value)
                {
                case ONE:
                    DrawTextEx(config.font, "1", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[ONE]);
                    break;
                case TWO:
                    DrawTextEx(config.font, "2", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[TWO]);
                    break;
                case THREE:
                    DrawTextEx(config.font, "3", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[THREE]);
                    break;
                case FOUR:
                    DrawTextEx(config.font, "4", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[FOUR]);
                    break;
                case FIVE:
                    DrawTextEx(config.font, "5", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[FIVE]);
                    break;
                case SIX:
                    DrawTextEx(config.font, "6", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[SIX]);
                    break;
                case SEVEN:
                    DrawTextEx(config.font, "7", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[SEVEN]);
                    break;
                case EIGHT:
                    DrawTextEx(config.font, "8", {(float)currentPosition.x + config.cellSize / 6, (float)currentPosition.y}, config.cellSize, 0, config.cellColors[EIGHT]);
                    break;
                default:
                    break;
                }
            }
            else
            {
                DrawRectangle(currentPosition.x, currentPosition.y, config.cellSize, config.cellSize, GRAY);
            }
            doubleArrayGrid[r][c].screenLocation = currentPosition;
            currentPosition.x += (config.cellSize + config.cellSpacing);
        }
        currentPosition.x = drawOffset.x;
        currentPosition.y += (config.cellSize + config.cellSpacing);
    }
}
Cell *Grid::getCellByPositionInArea(Position position)
{
    if (doubleArrayGrid[0][0].screenLocation.x != config.garbage)
    {
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (utility::isInBetween(position.x, doubleArrayGrid[r][c].screenLocation.x, doubleArrayGrid[r][c].screenLocation.x + 30) &&
                    utility::isInBetween(position.y, doubleArrayGrid[r][c].screenLocation.y, doubleArrayGrid[r][c].screenLocation.y + 30))
                {
                    return &(doubleArrayGrid[r][c]);
                }
            }
        }
        return NULL;
    }
    return NULL;
}
std::vector<Cell *> Grid::getSurroundingZeros(Position position)
{
    std::vector<Position> array;
    array.push_back(position);
    internalRecursive(position, &array);

    std::vector<Cell *> toRet;
    for (int i = 0; i < array.size(); i++)
    {
        toRet.push_back(getCell(array[i]));
    }
    return toRet;
}
void Grid::internalRecursive(Position working, std::vector<Position> *retrievalArray)
{
    int directions[][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i = 0; i < (sizeof(directions) / sizeof(directions[0])); i++)
    {
        int newX = working.x + directions[i][0];
        int newY = working.y + directions[i][1];
        if (utility::isValidCell(newX, newY, cols, rows) && utility::indexOf(*retrievalArray, {newX, newY}) == -1 && getCell(working)->value == ZERO)
        {
            retrievalArray->push_back({newX, newY});
            internalRecursive({newX, newY}, retrievalArray);
        }
        else
        {
            continue;
        }
    }
}
