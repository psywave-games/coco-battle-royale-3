#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include "header.h"

enum {
    fsm_player_died,
    fsm_player_idle,
    fsm_player_walk,
    fsm_player_atck
};

static struct player_t {
    float x;
    float y;
    float hspeed;
    float vspeed;
    unsigned char state;
    time_t last_attack;
}   player[MAX_PLAYERS];


void PlayerInit(char player_id)
{
    char player_near;
    bool near_enemy;
    bool near_player;

    player[player_id].state = fsm_player_idle;  
    player[player_id].hspeed = 0.0f;
    player[player_id].vspeed = 0.0f; 

    if (player_id == 0) {
        player[player_id].x = (DEFAULT_SCREEN_WIDTH/2) - (PLAYER_SIZE/2);
        player[player_id].y = (DEFAULT_SCREEN_HEIGHT/2) - (PLAYER_SIZE/2);
        return;
    }

    do {
        player[player_id].x = GetRandomValue(0, WORD_LIMIT_X);
		player[player_id].y = GetRandomValue(0, WORD_LIMIT_Y);

        player_near = PlayerNear(player_id, player[player_id].x, player[player_id].y);

        near_enemy = PlayerDistance(player_id, player_near)/PLAYER_SIZE < PLAYER_AWAY;
        near_player = PlayerDistance(player_id, 0)/PLAYER_SIZE < (PLAYER_AWAY * 2);
    } while (near_player || near_enemy);
}

void PlayerDraw(char player_id)
{
    DrawRectangle(
        player[player_id].x, 
        player[player_id].y,
        PLAYER_SIZE,
        PLAYER_SIZE,
        WHITE
    );
}

void PlayerStep(char player_id)
{
    int axis_x = 0;
    int axis_y = 0;

    if (player_id == 0) {
        axis_x = InputAxisX();
        axis_y = InputAxisY();
    }

    // FINITE STATE MACHINE PLAYER CONTROLL
    if (player[player_id].state == fsm_player_died){
        return;
    }
    else if (InputAttack() && player[player_id].last_attack + PLAYER_ATTACK_TIME < UNIX_TIME){
        player[player_id].last_attack = UNIX_TIME;
        player[player_id].state = fsm_player_atck;
    }
    else if (player[player_id].last_attack + PLAYER_ATTACK_TIME > UNIX_TIME) {
        player[player_id].state = fsm_player_atck;
    }
    else if (axis_x != 0 || axis_y != 0) {
        player[player_id].state = fsm_player_walk;
    }
    else {
        player[player_id].state = fsm_player_idle;
    }

    // MOVEMENT CHARACTER
    if (player[player_id].state == fsm_player_walk) {
        player[player_id].hspeed = Lerp(player[player_id].hspeed, PLAYER_MAX_SPEED * axis_x, PLAYER_INC_SPEED);
        player[player_id].vspeed = Lerp(player[player_id].vspeed, PLAYER_MAX_SPEED * axis_y, PLAYER_INC_SPEED);
        player[player_id].x = Clamp(player[player_id].x + (player[player_id].hspeed * GetFrameTime()), 0, WORD_LIMIT_X);
        player[player_id].y = Clamp(player[player_id].y + (player[player_id].vspeed * GetFrameTime()), 0, WORD_LIMIT_Y);
    }
}


char PlayerNear(char not_player_id, float x, float y)
{
    float distance_old = 0xFFFFFF;
    float distance_new = 0x00;
    char nearest = 0; 

    for (char player_near = 0; player_near < MAX_PLAYERS; player_near++) {
        
        if (player[player_near].state == fsm_player_died) {
            continue;
        }

        if (player_near == not_player_id){
            continue;
        }

        distance_new = PointDistance2D(x, y, player[player_near].x, player[player_near].y);

        if (distance_new <= distance_old) {
            distance_old = distance_new;
            nearest = player_near;
        }
    }

    return nearest;
}

float PlayerDistance(char player_a, char player_b)
{
    return PointDistance2D(player[player_a].x, player[player_a].y, player[player_b].x, player[player_b].y);
}