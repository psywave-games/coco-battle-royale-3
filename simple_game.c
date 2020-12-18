/*******************************************************************************************
*
*   raylib
*
*   Coco Battle Royale
*   <Game description>
*
********************************************************************************************/

#include <time.h> 
#include <raylib.h>
#include <stdbool.h>

#include "src/header.h"
#include "src/input.c"
#include "src/player.c"
#include "src/ia_bot.c"

static time_t game_time_init; 
static bool game_started;

int main(void)
{
    const int screenWidth = DEFAULT_SCREEN_WIDTH;
    const int screenHeight = DEFAULT_SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, GAME_TITLE);
    SetTargetFPS(1000);            

    while (!WindowShouldClose()) 
    {
        /// PREPARE GAME
        static bool pause = false;
        static bool reset = true;
        static bool fps = false;
        
        // RESET GAME
        if (reset) {
            for (player_t i = 0; i < MAX_PLAYERS; PlayerInit(i), i++);
            for (player_t i = 1; i < MAX_PLAYERS; BotIaInit(i), i++);
            game_time_init = UNIX_TIME;
            game_started = false;
            pause = false;
            reset = false;
        }

        // PRE-STEP GAME
        InputStep();
        PlayerMediatorStep();
        PlayerCountStep();

        // STEP GAME
        if (!pause && IsGameStarted()) {
            for (player_t i = 0; i < MAX_PLAYERS; PlayerStep(i), i++);
            for (player_t i = 0; i < MAX_PLAYERS; BotIaStep(i), i++);
        }

        // -------------------------------------------------------- //
        BeginDrawing();
        ClearBackground(BLACK);
        // players draw
        for (
            player_t i = 0, j = IsGameStarted()? MAX_PLAYERS: 1;
            i < j; PlayerDraw(i), i++
        );
        // draw text pause
        if (pause){
            DrawText("PAUSED!", 10, 64, 32, WHITE);
        }
        // draw text fp
        if (fps) {
            DrawFPS(10,0);
        } 
        // draw wait time
        if (!IsGameStarted()){
            const char* text = TextFormat("starting at %02d...", game_time_init + GAME_AWAIT - UNIX_TIME);
            DrawText(text, screenWidth/2, screenHeight/2, 32, WHITE);
        }
        
        EndDrawing();
        // -------------------------------------------------------- //

        // END STEP
        fps = IsKeyPressed(KEY_F)? !fps: fps;
        pause = IsKeyPressed(KEY_P)? !pause: pause;
        reset = IsKeyPressed(KEY_R);
    }

    CloseWindow();   
    return 0;
}

bool IsGameStarted()
{
    if (game_started) {
        return true;
    }

    if (game_time_init + GAME_AWAIT <= UNIX_TIME) {
        game_started = true;
        return true;
    }

    return false;
}