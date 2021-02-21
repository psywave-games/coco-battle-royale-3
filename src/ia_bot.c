#include "header.h"

enum {
    fsm_ia_none,
    fsm_ia_winner,
    fsm_ia_hunter,
    fsm_ia_escape,
    fsm_ia_random,
    fsm_ia_sleep,
};

struct ia_s {
    bool attack;
    state_t state;
    player_t target; 
    axis_i_t input_x;
    axis_i_t input_y;
}   bot[(player_t) MAX_PLAYERS];

void BotIaInit(player_t player_id)
{
    BotIaChange(player_id);
}

void BotIaStep(player_t player_id)
{
    if (PlayerDeath(player_id)){
        bot[player_id].state = fsm_ia_none;
        return;
    }

    if (PlayerCount() <= 1) {
        bot[player_id].state = fsm_ia_winner;
        bot[player_id].attack = false;
    }

    switch (bot[player_id].state) {
        case fsm_ia_winner:
            // ADJUST VERTICAL|HORIZONTAL
            {
                Vector2 pos = PlayerPos(player_id);
                int dis_middle = (DEFAULT_SCREEN_HEIGHT/2) - ((int) pos.y);
                int dis_center = (DEFAULT_SCREEN_WIDTH/2) - ((int) pos.x);

                // VERTICAL INPUT
                if (abs(dis_middle) > 5 && dis_middle < 0) {
                    bot[player_id].input_y = -1;
                } 
                else if (abs(dis_middle) > 5 && dis_middle > 0) {
                    bot[player_id].input_y = 1;
                }
                else {
                    bot[player_id].input_y = 0;
                }

                // HORIZONTAL INPUT
                if (abs(dis_center) > (DEFAULT_SCREEN_WIDTH/4) && dis_center < 0) {
                    bot[player_id].input_x = -1;
                } 
                else if (abs(dis_center) > (DEFAULT_SCREEN_WIDTH/4) && dis_center > 0) {
                    bot[player_id].input_x = 1;
                }
            }
            break;


        case fsm_ia_sleep:
            if (GetRandomValue(0, 25) == 0){
                BotIaChange(player_id);
            } else {
                bot[player_id].input_x = 0;
                bot[player_id].input_y = 0;
            }  
            break;

        case fsm_ia_random:
            if (GetRandomValue(0, 100) == 0) {
                bot[player_id].input_x = GetRandomValue(-1, 1);
                bot[player_id].input_y = GetRandomValue(-1, 1);
            } 
            else if (GetRandomValue(0, 50) == 0){
                BotIaChange(player_id);
            }  
            break;

        case fsm_ia_hunter:
            if (PlayerDeath(bot[player_id].target)) {
                BotIaRetarget(player_id);
            }
            else if (PlayerDistance(bot[player_id].target, player_id) < PLAYER_SIZE) {
                bot[player_id].attack = GetRandomValue(0, 3) == 0;
            }
            else if (GetRandomValue(0, 15) == 0 && PlayerDistance(bot[player_id].target, player_id) > (PLAYER_SIZE * 5)) {
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

void BotIaRetarget(player_t player_id)
{
    Vector2 player_pos = PlayerPos(player_id);
    bot[player_id].target = PlayerNear(player_id, player_pos.x, player_pos.y);
    bot[player_id].attack = false;
}

void BotIaChange(player_t player_id)
{
    BotIaRetarget(player_id);
    switch (bot[player_id].state) {
        case fsm_ia_escape:
            bot[player_id].state = fsm_ia_random;
            break;

        default:
            bot[player_id].state = GetRandomValue(fsm_ia_hunter, fsm_ia_sleep);
            break;
    }
}

bool BotAttack(player_t player_id)
{
    return bot[player_id].attack;
}

int BotAxisX(player_t player_id)
{
    return (int) bot[player_id].input_x;
}

int BotAxisY(player_t player_id)
{
    return (int) bot[player_id].input_y;
}