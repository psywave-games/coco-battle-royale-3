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
    SetTargetFPS(1000);            


    while (!WindowShouldClose()) 
    {
        static bool pause = false;
        static bool reset = true;
        
        // RESET GAME
        if (reset) {
            for (char i = 0; i < MAX_PLAYERS; PlayerInit(i), i++);
            pause = false;
            reset = false;
        }

        // PRE-STEP GAME
        InputStep();

        // STEP GAME
        if (!pause) {
            for (char i = 0; i < MAX_PLAYERS; PlayerStep(i), i++);
        }

        // DRAW GAME
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10,0);
        for (char i = 0; i < MAX_PLAYERS; PlayerDraw(i), i++);
        if (pause){
            DrawText("PAUSED!", 10, 64, 32, WHITE);
        }
        EndDrawing();

        // END STEP
        pause = IsKeyPressed(KEY_P)? !pause: pause;
        reset = IsKeyPressed(KEY_R);
    }

    CloseWindow();   
    return 0;
}
