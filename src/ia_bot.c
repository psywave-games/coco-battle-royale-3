#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include "header.h"

static enum {
    fsm_ia_winner,
    fsm_ia_hunter,
    fsm_ia_escape,
    fsm_ia_random,
    fsm_ia_sleep,
};

static struct ia_t {
    bool attack;
    unsigned char state;
    unsigned char target; 
    signed char input_x;
    signed char input_y;
}   bot[MAX_PLAYERS];

void BotIaInit(char player_id)
{
    BotIaChange(player_id);
    BotIaRetarget(player_id);
}

void BotIaStep(void)
{
    for (char player_id = 0; player_id < MAX_PLAYERS; player_id++)
    {
        switch (bot[player_id].state) {
            case fsm_ia_sleep:
                if (GetRandomValue(0, 25) == 0){
                    BotIaChange(player_id);
                } else {
                    bot[player_id].input_x = 0;
                    bot[player_id].input_y = 0;
                }  
                break;

            case fsm_ia_random:
                if (GetRandomValue(0, 50) == 0) {
                    bot[player_id].input_x = GetRandomValue(-1, 1);
                    bot[player_id].input_y = GetRandomValue(-1, 1);
                } 
                else if (GetRandomValue(0, 25) == 0){
                    BotIaChange(player_id);
                }  
                break;

            case fsm_ia_hunter:
                if (GetRandomValue(0, 200) == 0) {
                    BotIaRetarget(player_id);
                } 
                else if (PlayerDistance(bot[player_id].target, player_id) < PLAYER_SIZE) {
                    bot[player_id].attack = GetRandomValue(0, 3) == 0;
                }
                else if (PlayerDistance(bot[player_id].target, player_id) > (PLAYER_SIZE * 5)) {
                    BotIaChange(player_id);
                } 
                else {
                    Vector2 player_hunter_pos = PlayerPos(player_id);
                    Vector2 player_escape_pos = PlayerPos(bot[player_id].target);
                    bot[player_id].input_x = player_hunter_pos.x < player_escape_pos.x? 1: -1;
                    bot[player_id].input_y = player_hunter_pos.y < player_escape_pos.y? 1: -1;
                }
                break;  

            case fsm_ia_escape:
                if (PlayerDistance(bot[player_id].target, player_id) > (PLAYER_SIZE * 5)) {
                    BotIaChange(player_id);
                }
                else if (GetRandomValue(0, 10) == 0) {
                    BotIaRetarget(player_id);
                } 
                else {
                    Vector2 player_hunter_pos = PlayerPos(bot[player_id].target);
                    Vector2 player_escape_pos = PlayerPos(player_id);
                    bot[player_id].input_x = player_hunter_pos.x < player_escape_pos.x? 1: -1;
                    bot[player_id].input_y = player_hunter_pos.y < player_escape_pos.y? 1: -1;
                }
                break;    
        }
    }
}

void BotIaRetarget(char player_id)
{
    Vector2 player_pos = PlayerPos(player_id);
    bot[player_id].target = PlayerNear(player_id, player_pos.x, player_pos.y);
}

void BotIaChange(char player_id)
{
    switch (bot[player_id].state) {
        case fsm_ia_escape:
            bot[player_id].state = fsm_ia_random;
            break;

        default:
            bot[player_id].state = GetRandomValue(fsm_ia_hunter, fsm_ia_sleep);
            break;
    }
}

bool BotAttack(char player_id)
{
    return bot[player_id].state == fsm_ia_hunter? bot[player_id].attack: false;
}

int BotAxisX(char player_id)
{
    return (int) bot[player_id].input_x;
}

int BotAxisY(char player_id)
{
    return (int) bot[player_id].input_y;
}