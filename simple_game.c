/*******************************************************************************************
*
*   raylib
*
*   Coco Battle Royale
*   <Game description>
*
********************************************************************************************/

#include "src/color.c"
#include "src/input.c"
#include "src/player.c"
#include "src/ia_bot.c"

static Tick game_tickets;
static player_t game_rank;

int main(void)
{
    const int screenWidth = DEFAULT_SCREEN_WIDTH;
    const int screenHeight = DEFAULT_SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, GAME_TITLE);
    SetTargetFPS(GAME_FPS);            

    while (!WindowShouldClose()) 
    {
        /// PREPARE GAME
        static bool pause = false;
        static bool reset = true;
        static bool fps = false;
        
        // RESET GAME
        if (reset) {
            ColorBackground(true);
            for (player_t i = 0; i < MAX_PLAYERS; PlayerInit(i), i++);
            for (player_t i = 1; i < MAX_PLAYERS; BotIaInit(i), i++);
            game_tickets = 0;
            pause = false;
            reset = false;
        }

        // PRE-STEP GAME
        InputStep();
        PlayerMediatorStep();
        PlayerCountStep();
        game_tickets += !pause;

        // STEP GAME
        if (!pause && IsGameStarted()) {
            for (player_t i = 0; i < MAX_PLAYERS; PlayerStep(i), i++);
            for (player_t i = 0; i < MAX_PLAYERS; BotIaStep(i), i++);
        }

        // PLAYER SCORE
        if (!PlayerDeath(0)) {
            game_rank = PlayerCount();
        }

        // -------------------------------------------------------- //
        BeginDrawing();
        ClearBackground(ColorBackground(false));
        // players draw
        for (
            player_t i = 0, j = IsGameStarted()? MAX_PLAYERS: 1;
            i < j; PlayerDraw(i), i++
        );
        // draw text pause
        if (pause){
            DrawText("PAUSED!", 10, 64, 32, LIGHTGRAY);
        }
        // draw text fp
        if (fps) {
            DrawFPS(10,0);
        } 
        // draw wait time
        if (!IsGameStarted()){
            const char* text = TextFormat("starting at %02d...", GAME_AWAIT - (game_tickets/GAME_FPS));
            DrawText(text, screenWidth/2, screenHeight/2, 32, LIGHTGRAY);
        }

        // draw game over
        if (PlayerCount() <= 1){
            const char* text = PlayerDeath(0)? 
                TextFormat("#%02d\nYou were fried.", game_rank):
                "#1\nYou Are\nUltimate\nHot Chicken!!";

            DrawText(text, screenWidth/2, screenHeight/2, 32, LIGHTGRAY);
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
    return (GAME_FPS * GAME_AWAIT) < game_tickets;
}

Tick GameStep()
{
    return game_tickets;
}