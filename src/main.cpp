#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "config.h"
#include "utility.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
bool hasWon;
void FirstFrame_menu()
{
}
bool DetermineWin(Grid grid)
{
    bool won = true;
    for (int y = 0; y < grid.rows; y++)
    {
        for (int x = 0; x < grid.cols; x++)
        {
            if (!(grid.getCell({x, y})->discovered) && utility::indexOf(grid.mineLocations, {x, y}) == -1)
            {
                won = false;
            }
        }
    }
    return won;
}
int main()
{
    int timeTakenToWin;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minesweeper");
    SetTargetFPS(60);
    SetExitKey(KEY_DELETE);
    config.font = LoadFontEx("resources/main.otf", 120, 0, 250);
    config.mineCount = 40;
    config.cellSize = 34;
    config.cellSpacing = 6;
    config.rows = 18;
    config.cols = 18;
    Grid grid = Grid(100, 100);
    // TODO: Make menu screen
    while (!WindowShouldClose())
    {
        if (config.gameState == MENU)
        {
            if (IsKeyPressed(KEY_ENTER) && config.framesElapsedSinceModeChange > 120)
            {
                if (config.difficulty == EASY)
                {
                    config.rows = 10, config.cols = 10, config.mineCount = 10, config.cellSize = 62, config.cellSpacing = 10;
                }
                else if (config.difficulty == NORMAL)
                {
                    config.rows = 18, config.cols = 18, config.mineCount = 40, config.cellSize = 34, config.cellSpacing = 6;
                }
                else if (config.difficulty == HARD)
                {
                    config.rows = 24, config.cols = 24, config.mineCount = 99, config.cellSize = 26, config.cellSpacing = 4;
                }
                grid.reset(config.rows, config.cols);
                config.framesElapsedSinceModeChange = 0;
                config.gameState = GAME;
            }
            else if (IsKeyPressed(KEY_LEFT))
            {
                if (config.difficulty == EASY)
                {
                    config.difficulty = HARD;
                }
                else
                {
                    config.difficulty = (Difficulty)((int)config.difficulty - 1);
                }
            }
            else if (IsKeyPressed(KEY_RIGHT))
            {
                if (config.difficulty == HARD)
                {
                    config.difficulty = EASY;
                }
                else
                {
                    config.difficulty = (Difficulty)((int)config.difficulty + 1);
                }
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            DrawTextEx(config.font, "Minesweeper", {40, 40}, 120, 0, WHITE);
            DrawText("Another simple raylib game by omger.", 40, 200, 30, WHITE);
            DrawText("Use left click to dig.", 40, 260, 30, WHITE);
            DrawText("Use right click to place a flag.", 40, 290, 30, WHITE);
            DrawText("If you discover a mine, you lose.", 40, 320, 30, WHITE);
            DrawText("You win once everywhere except the mines is clear.", 40, 350, 30, WHITE);
            DrawTextEx(config.font, "Press ENTER to start", {40, 410}, 60, 0, WHITE);
            DrawText(TextFormat("Press arrows to change difficulty: %s", config.difficulty == EASY ? "Easy" : (config.difficulty == NORMAL ? "Normal" : "Hard")), 40, 500, 30, WHITE);
            DrawText("Release version 1.0", 40, SCREEN_HEIGHT - 90, 30, WHITE);
            DrawText("Press delete to exit", 40, SCREEN_HEIGHT - 60, 30, WHITE);
            if (utility::isInBetween(config.framesElapsedSinceModeChange, 60, 120))
            {
                DrawRectangle(0, 160 + (SCREEN_HEIGHT - 160) * 1 / 60 * (config.framesElapsedSinceModeChange - 60), SCREEN_WIDTH, SCREEN_HEIGHT, {26, 14, 130, 255});
            }
            else if (config.framesElapsedSinceModeChange <= 60)
            {
                DrawRectangle(0, 160, SCREEN_WIDTH, SCREEN_HEIGHT, {26, 14, 130, 255});
            }
            EndDrawing();
        }
        else if (config.gameState == GAME)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (grid.getCellByPositionInArea({GetMouseX(), GetMouseY()}))
                {
                    grid.getCellByPositionInArea({GetMouseX(), GetMouseY()})->onClick(GetMouseX(), GetMouseY());
                    hasWon = DetermineWin(grid);
                    if (hasWon)
                    {
                        config.gameState = WIN;
                        timeTakenToWin = config.framesElapsedSinceModeChange / 60;
                        config.framesElapsedSinceModeChange = 0;
                        continue;
                    }
                }
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                if (grid.getCellByPositionInArea({GetMouseX(), GetMouseY()}))
                {
                    Cell *toFlag = grid.getCellByPositionInArea({GetMouseX(), GetMouseY()});
                    if ((config.mineCount - grid.flagCount) > 0 && !toFlag->discovered)
                    {
                        toFlag->isFlagged = !(toFlag->isFlagged);
                        if (toFlag->isFlagged)
                        {
                            grid.flagCount++;
                        }
                        else
                        {
                            grid.flagCount--;
                        }
                    }
                }
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            grid.drawOffset = {0, 0};
            grid.drawGrid();
            DrawText(TextFormat("F: %i", config.mineCount - grid.flagCount), 760, 40, 60, RED);
            DrawText(TextFormat("T: %i", config.framesElapsedSinceModeChange / 60), 760, 140, 60, WHITE);
            EndDrawing();
        }
        else if (config.gameState == WIN)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                grid.reset(config.rows, config.cols);
                config.framesElapsedSinceModeChange = 0;
                config.gameState = GAME;
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            DrawTextEx(config.font, "#1 victory royale", {40, 40}, 90, 0, WHITE);
            DrawText(TextFormat("%i seconds", timeTakenToWin), 40, 150, 60, WHITE);
            DrawText("Press ENTER to play again", 40, 230, 60, WHITE);
            EndDrawing();
        }
        else if (config.gameState == LOSS)
        {
            if (config.framesElapsedSinceModeChange >= 120)
            {
                break;
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            DrawTextEx(config.font, "You took an L", {40, 40}, 90, 0, WHITE);
            DrawText(TextFormat("I will close the game in %i frames to be annoying", 120 - config.framesElapsedSinceModeChange), 40, 150, 45, WHITE);
            EndDrawing();
        }

        config.framesElapsedSinceModeChange++;
    }
    UnloadFont(config.font);
    CloseWindow();
    return 0;
}