#include <iostream>
#include <raylib.h>
#include "grid.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int framesElapsedSinceModeChange = 0;
int main()
{
    Grid grid = Grid(10,10);
    grid.setValue(Position{4, 1}, 1);
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Template");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        framesElapsedSinceModeChange++;
    }
    CloseWindow();
    
}