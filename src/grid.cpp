#include "grid.h"
#include "position.h"
#include <iostream>
#include <raylib.h>
#include "config.h"
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
}
// Note that position is in grid cells.
Cell Grid::getCell(Position position)
{
    return doubleArrayGrid[position.y][position.x];
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
                if ((position.y > doubleArrayGrid[r][c].screenLocation.y && (r >= rows - 1 ? true : position.y <= doubleArrayGrid[r + 1][c].screenLocation.y)) && (position.x > doubleArrayGrid[r][c].screenLocation.x && (c >= rows - 1 ? true : position.x <= doubleArrayGrid[r][c + 1].screenLocation.x)))
                {
                    return &(doubleArrayGrid[r][c]);
                }
            }
        }
        return &(doubleArrayGrid[rows - 1][cols - 1]);
    }
    return &(doubleArrayGrid[0][0]);
}