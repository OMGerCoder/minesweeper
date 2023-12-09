#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "config.h"
#include "minesweeperGrid.h"
#include "utility.h"
const int SCREEN_WIDTH = 1042;
const int SCREEN_HEIGHT = 695;
enum GameState
{
    MENU = 0,
    GAME = 1,
    WIN = 2
};
GameState gameState = MENU;
int framesElapsedSinceModeChange = 0;
bool hasWon;
void FirstFrame_menu()
{
}
bool DetermineWin(MinesweeperGrid grid)
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
    config.font = LoadFontEx("build/resources/main.otf", config.cellSize, 0, 250);
    config.mineCount = 30;
    config.cellSize = 30;
    config.cellSpacing = 5;
    config.rows = 20;
    config.cols = 20;
    MinesweeperGrid grid = MinesweeperGrid(config.rows, config.cols);
    // TODO: Make menu screen
    while (!WindowShouldClose())
    {
        if (gameState == MENU)
        {
            if (IsKeyPressed(KEY_ENTER) && framesElapsedSinceModeChange > 120)
            {
                grid.reset(config.rows, config.cols);
                framesElapsedSinceModeChange = 0;
                gameState = GAME;
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            DrawText("Minesweeper", 40, 40, 120, WHITE);
            DrawText("Another simple raylib game by omger.", 40, 200, 30, WHITE);
            DrawText("Use left click to dig.", 40, 260, 30, WHITE);
            DrawText("Use right click to place a flag.", 40, 290, 30, WHITE);
            DrawText("If you discover a mine, you lose.", 40, 320, 30, WHITE);
            DrawText("You win once everywhere except the mines is clear.", 40, 350, 30, WHITE);
            DrawText("Press ENTER to start", 40, 410, 60, WHITE);
            DrawText("Release version 1.0", 40, SCREEN_HEIGHT - 90, 30, WHITE);
            DrawText("Press delete to exit", 40, SCREEN_HEIGHT - 60, 30, WHITE);
            if (utility::isInBetween(framesElapsedSinceModeChange, 60, 120))
            {
                DrawRectangle(0, 160 + (SCREEN_HEIGHT - 160) * 1 / 60 * (framesElapsedSinceModeChange - 60), SCREEN_WIDTH, SCREEN_HEIGHT, {26, 14, 130, 255});
            }
            else if (framesElapsedSinceModeChange <= 60)
            {
                DrawRectangle(0, 160, SCREEN_WIDTH, SCREEN_HEIGHT, {26, 14, 130, 255});
            }
            EndDrawing();
        }
        else if (gameState == GAME)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (grid.getCellByPositionInArea({GetMouseX(), GetMouseY()}))
                {
                    grid.getCellByPositionInArea({GetMouseX(), GetMouseY()})->onClick(GetMouseX(), GetMouseY());
                    hasWon = DetermineWin(grid);
                    if (hasWon)
                    {
                        gameState = WIN;
                        timeTakenToWin = framesElapsedSinceModeChange / 60;
                        framesElapsedSinceModeChange = 0;
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
            DrawText(TextFormat("F: %i", config.mineCount - grid.flagCount), 735, 40, 60, RED);
            DrawText(TextFormat("T: %i", framesElapsedSinceModeChange / 60), 735, 140, 60, WHITE);
            EndDrawing();
        }
        else if (gameState == WIN)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                grid.reset(config.rows, config.cols);
                framesElapsedSinceModeChange = 0;
                gameState = GAME;
            }
            BeginDrawing();
            ClearBackground({26, 14, 130, 255});
            DrawText("#1 victory royale", 40, 40, 90, WHITE);
            DrawText(TextFormat("%i seconds", timeTakenToWin), 40, 150, 60, WHITE);
            DrawText("Press ENTER to play again", 40, 230, 60, WHITE);
            EndDrawing();
        }
        framesElapsedSinceModeChange++;
    }
    UnloadFont(config.font);
    CloseWindow();
    return 0;
}