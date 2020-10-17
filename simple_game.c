/*******************************************************************************************
*
*   raylib
*
*   Coco Battle Royale
*   <Game description>
*
********************************************************************************************/

#include <raylib.h>

#include "src/header.h"
#include "src/input.c"
#include "src/player.c"

int main(void)
{
    const int screenWidth = DEFAULT_SCREEN_WIDTH;
    const int screenHeight = DEFAULT_SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, GAME_TITLE);
    SetTargetFPS(60);            

    for (char i = 0; i < MAX_PLAYERS; PlayerInit(i), i++);

    while (!WindowShouldClose()) 
    {
        InputStep();
        for (char i = 0; i < MAX_PLAYERS; PlayerStep(i), i++);

        BeginDrawing();
        ClearBackground(BLACK);

        for (char i = 0; i < MAX_PLAYERS; PlayerDraw(i), i++);
        
        EndDrawing();
    }

    CloseWindow();   
    return 0;
}
