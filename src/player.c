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
    bool sign;
    unsigned char state;
    time_t last_attack;
    Color color;
}   player[MAX_PLAYERS];


void PlayerInit(char player_id)
{
    char player_near;
    bool near_enemy;
    bool near_player;

    player[player_id].state = fsm_player_idle;  
    player[player_id].color = (Color) {irand(255), irand(255), irand(255), 255};
    player[player_id].hspeed = 0.0f;
    player[player_id].vspeed = 0.0f; 

    if (player_id == 0) {
        player[player_id].sign = SIDE_RIGHT;
        player[player_id].x = (DEFAULT_SCREEN_WIDTH/2) - (PLAYER_SIZE/2);
        player[player_id].y = (DEFAULT_SCREEN_HEIGHT/2) - (PLAYER_SIZE/2);
        return;
    }

    do {
        player[player_id].x = irand(WORD_LIMIT_X);
		player[player_id].y = irand(WORD_LIMIT_Y);

        player_near = PlayerNear(player_id, player[player_id].x, player[player_id].y);

        near_enemy = PlayerDistance(player_id, player_near)/PLAYER_SIZE < PLAYER_AWAY;
        near_player = PlayerDistance(player_id, 0)/PLAYER_SIZE < (PLAYER_AWAY * 2);
    } while (near_player || near_enemy);
}

void PlayerDraw(char player_id)
{
    Vector2 aux_v;
    Color color_outline = player_id? player[player_id].color: WHITE;
    Color color_inshape = player_id? WHITE: player[player_id].color;
    static signed char player_ancor_x = 8;
    static signed char player_ancor_y = 12;
    static signed char trinagle_primary_x1 = 5;
    static signed char trinagle_primary_y1 = 10;
    static signed char trinagle_primary_x2 = 5;
    static signed char trinagle_primary_y2 = 20;
    static signed char trinagle_primary_x3 = 14;
    static signed char trinagle_primary_y3 = 10;
    static signed char trinagle_secondary_x1 = 0;
    static signed char trinagle_secondary_y1 = 10;
    static signed char trinagle_secondary_x2 = 3;
    static signed char trinagle_secondary_y2 = 16;
    static signed char trinagle_secondary_x3 = 3;
    static signed char trinagle_secondary_y3 = 10;
    static signed char trinagle_third_x1 = 3;
    static signed char trinagle_third_y1 = 6;
    static signed char trinagle_third_x2 = 0;
    static signed char trinagle_third_y2 = 8;
    static signed char trinagle_third_x3 = 3;
    static signed char trinagle_third_y3 = 8;
    static signed char square_head_x = 12;
    static signed char square_head_y = 1;

    // PLAYER RENDER STATE 
    switch (player[player_id].state) {
        case fsm_player_atck:
            DrawCircleLines(player[player_id].x, player[player_id].y, PLAYER_SIZE, RED);

        case fsm_player_walk:
        case fsm_player_idle: {
            // Triangle Primary|Seecondary|Third Point A|B|C
            Vector2 tppa = {player[player_id].x + ((trinagle_primary_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_primary_y1 - player_ancor_y};
            Vector2 tppb = {player[player_id].x + ((trinagle_primary_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_primary_y2 - player_ancor_y};
            Vector2 tppc = {player[player_id].x + ((trinagle_primary_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_primary_y3 - player_ancor_y};
            Vector2 tspa = {player[player_id].x + ((trinagle_secondary_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_secondary_y1 - player_ancor_y};
            Vector2 tspb = {player[player_id].x + ((trinagle_secondary_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_secondary_y2 - player_ancor_y};
            Vector2 tspc = {player[player_id].x + ((trinagle_secondary_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_secondary_y3 - player_ancor_y};
            Vector2 ttpa = {player[player_id].x + ((trinagle_third_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_third_y1 - player_ancor_y};
            Vector2 ttpb = {player[player_id].x + ((trinagle_third_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_third_y2 - player_ancor_y};
            Vector2 ttpc = {player[player_id].x + ((trinagle_third_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + trinagle_third_y3 - player_ancor_y};

            // force clock-wise trinagle
            if (player[player_id].sign == SIDE_LEFT){
                // trinagle primary
                aux_v = tppb;
                tppb = tppc;
                tppc = aux_v;
                // trinagle secondary
                aux_v = tspb;
                tspb = tspc;
                tspc = aux_v;
                // trinagle third
                aux_v = ttpb;
                ttpb = ttpc;
                ttpc = aux_v;
            }

            /// Square Head Point|Size
            Vector2 shp = {player[player_id].x + ((square_head_x  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + square_head_y - player_ancor_y};
            Vector2 shs = {3, 6};

            /// Render In Shape
            DrawTriangle(tppa, tppb, tppc, color_inshape);
            DrawTriangle(tspa, tspb, tspc, color_inshape);
            DrawTriangle(ttpa, ttpb, ttpc, color_inshape);
            DrawRectangleV(shp, shs, color_inshape);

            DrawTriangleLines(tppa, tppb, tppc, color_outline);
            DrawTriangleLines(tspa, tspb, tspc, color_outline);
            DrawTriangleLines(ttpa, ttpb, ttpc, color_outline);
            DrawRectangleLines(shp.x, shp.y, shs.x, shs.y, color_outline);
            break;
        }
    }
}

void PlayerStep(char player_id)
{
    int axis_x = 0;
    int axis_y = 0;
    bool attack = false;

    if (player_id == 0) {
        axis_x = InputAxisX();
        axis_y = InputAxisY();
        attack = InputAttack();
    } else {
        axis_x = BotAxisX(player_id);
        axis_y = BotAxisY(player_id);
        attack = BotAttack(player_id);
    }

    // FINITE STATE MACHINE PLAYER CONTROLL
    if (player[player_id].state == fsm_player_died){
        return;
    }
    else if (attack && player[player_id].last_attack + PLAYER_ATTACK_TIME < UNIX_TIME){
        player[player_id].last_attack = UNIX_TIME;
        player[player_id].state = fsm_player_atck;
    }
    else if (player[player_id].state == fsm_player_atck && player[player_id].last_attack + PLAYER_ATTACK_TIME > UNIX_TIME) {
        player[player_id].state = fsm_player_atck;
    }
    else if (axis_x != 0 || axis_y != 0) {
        player[player_id].state = fsm_player_walk;
        player[player_id].sign = axis_x > 0;
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

void PlayerMediatorStep(void)
{
    for (char i = 0; i < MAX_PLAYERS; i++) {
        if (player[i].state != fsm_player_atck) {
            continue;
        }
        
        for (char j = 0; j < MAX_PLAYERS; j++) {

            if (player[j].state == fsm_player_atck || player[j].state == fsm_player_died) {
                continue;
            }

            if (PlayerDistance(i, j) < PLAYER_SIZE) {
                player[i].state = fsm_player_idle;
                player[j].state = fsm_player_died;
            }
        }
    }
}

bool PlayerDeath(char player_id)
{
    return player[player_id].state == fsm_player_died;
}

Vector2 PlayerPos(char player_id)
{
    Vector2 pos = {player[player_id].x, player[player_id].y};
    return pos;
}