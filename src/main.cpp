#include <iostream>
#include <raylib.h>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
int framesElapsedSinceModeChange = 0;
int main()
{
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