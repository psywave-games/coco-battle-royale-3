#include <raylib.h>
#include <raymath.h>
#include "header.h"

static struct player_t {
    float x;
    float y;
    float hspeed;
    float vspeed;
}   player[MAX_PLAYERS];



void PlayerInit(int player_id)
{
    if (player_id == 0) {
        player[player_id].x = DEFAULT_SCREEN_WIDTH/2;
        player[player_id].y = DEFAULT_SCREEN_HEIGHT/2;
        return;
    }
}

void PlayerDraw(int player_id)
{
    DrawRectangle(
        player[player_id].x, 
        player[player_id].y,
        32,
        32,
        WHITE
    );
}

void PlayerStep(int player_id)
{
    int axis_x = 0;
    int axis_y = 0;

    if (player_id == 0) {
        axis_x = InputAxisX();
        axis_y = InputAxisY();
    }

    // player movement
    player[player_id].hspeed = Lerp(player[player_id].hspeed, PLAYER_MAX_SPEED * axis_x, PLAYER_INC_SPEED);
    player[player_id].vspeed = Lerp(player[player_id].vspeed, PLAYER_MAX_SPEED * axis_y, PLAYER_INC_SPEED);
    player[player_id].x += player[player_id].hspeed * GetFrameTime();
    player[player_id].y += player[player_id].vspeed * GetFrameTime();
}