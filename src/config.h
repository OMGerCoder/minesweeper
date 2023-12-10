#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include "grid.h"
enum GameState
{
    MENU = 0,
    GAME = 1,
    WIN = 2,
    LOSS = 3
};
enum Difficulty
{
    EASY = 0,
    NORMAL = 1,
    HARD = 2
};
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
    GameState gameState;
    int framesElapsedSinceModeChange;
    Difficulty difficulty;
    Config();
};
extern struct Config config;