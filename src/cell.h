#pragma once
#include "position.h"
#include "grid.h"

class Grid;
enum CellValues
{
    NIL = 0,
    MINE = 1,
    ZERO = 2,
    ONE = 3,
    TWO = 4,
    THREE = 5,
    FOUR = 6,
    FIVE = 7,
    SIX = 8,
    SEVEN = 9,
    EIGHT = 10
};
class Cell
{
public:
    Cell(CellValues valuein, Grid *parent, Position locRowCol);
    ~Cell();
    CellValues value;
    bool discovered;
    Position screenLocation;
    Position loc;
    void onClick(int mouseX, int mouseY);
    Grid *parent;
    bool isFlagged;
};