#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "grid.h"
struct Config
{
    int cellSize;
    int cellSpacing;
    int mineCount;
    int rows;
    int cols;
    Font font;
    std::map<CellValues, Color> cellColors;
    int garbage;
    Config();
};
extern struct Config config;