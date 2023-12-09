#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "config.h"
#include "minesweeperGrid.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int framesElapsedSinceModeChange = 0;
void FirstFrame_menu()
{
}
void FirstFrame_main()
{
}
int main()
{
    config.mineCount = 10;
    MinesweeperGrid grid = MinesweeperGrid(10, 10);
    config.cellSize = 60;
    config.cellSpacing = 10;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Template");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    config.font = LoadFontEx("build/resources/main.otf", config.cellSize, 0, 250);
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            grid.getCellByPositionInArea({GetMouseX(), GetMouseY()})->onClick(GetMouseX(), GetMouseY());
        }
        BeginDrawing();
        ClearBackground({26, 14, 130, 255});
        grid.drawOffset = {0, 0};
        grid.drawGrid();
        EndDrawing();
        framesElapsedSinceModeChange++;
    }
    UnloadFont(config.font);
    CloseWindow();
    return 0;
}