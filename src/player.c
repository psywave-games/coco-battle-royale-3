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

struct player_s {
    float x;
    float y;
    float hspeed;
    float vspeed;
    axis_b_t sign;
    state_t state;
    time_t last_attack;
    Color color;
}   player[(player_t) MAX_PLAYERS];

static player_t players_count;

void PlayerInit(player_t player_id)
{
    player_t player_near;
    bool near_enemy;
    bool near_player;

    player[player_id].state = fsm_player_idle;  
    player[player_id].color = RANDOM_COLOR;
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

void PlayerDraw(player_t player_id)
{
    Vector2 aux_v;
    Color color_outline = player_id? player[player_id].color: WHITE;
    Color color_inshape = player_id? WHITE: player[player_id].color;
    static signed char player_ancor_x = 32;
    static signed char player_ancor_y = 24;
    static signed char triangle_primary_x1 = 20;
    static signed char triangle_primary_y1 = 16;
    static signed char triangle_primary_x2 = 20;
    static signed char triangle_primary_y2 = 46;
    static signed char triangle_primary_x3 = 50;
    static signed char triangle_primary_y3 = 16;
    static signed char triangle_secondary_x1 = 6;
    static signed char triangle_secondary_y1 = 18;
    static signed char triangle_secondary_x2 = 16;
    static signed char triangle_secondary_y2 = 40;
    static signed char triangle_secondary_x3 = 16;
    static signed char triangle_secondary_y3 = 18;
    static signed char triangle_third_x1 = 16;
    static signed char triangle_third_y1 = 4;
    static signed char triangle_third_x2 = 6;
    static signed char triangle_third_y2 = 14;
    static signed char triangle_third_x3 = 16;
    static signed char triangle_third_y3 = 14;
    static signed char triangle_fourth_x1 = 50;
    static signed char triangle_fourth_y1 = 8;
    static signed char triangle_fourth_x2 = 50;
    static signed char triangle_fourth_y2 = 10;
    static signed char triangle_fourth_x3 = 56;
    static signed char triangle_fourth_y3 = 8;
    static signed char square_head_x = 42;
    static signed char square_head_y = 0;
    static signed char circle_eye_x = 46;
    static signed char circle_eye_y = 4;

    // PLAYER RAINBOW WINNER COLOR
    if (PlayerCount() <= 1){
        player[player_id].color = RANDOM_COLOR;
    }

    // PLAYER RENDER STATE 
    switch (player[player_id].state) {
        case fsm_player_atck:
            DrawCircleLines(player[player_id].x, player[player_id].y, PLAYER_SIZE, RED);

        case fsm_player_walk:
        case fsm_player_idle: {
            // Triangle Primary|Seecondary|Third|Fourth Point A|B|C
            Vector2 tppa = {player[player_id].x + ((triangle_primary_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_primary_y1 - player_ancor_y};
            Vector2 tppb = {player[player_id].x + ((triangle_primary_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_primary_y2 - player_ancor_y};
            Vector2 tppc = {player[player_id].x + ((triangle_primary_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_primary_y3 - player_ancor_y};
            Vector2 tspa = {player[player_id].x + ((triangle_secondary_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_secondary_y1 - player_ancor_y};
            Vector2 tspb = {player[player_id].x + ((triangle_secondary_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_secondary_y2 - player_ancor_y};
            Vector2 tspc = {player[player_id].x + ((triangle_secondary_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_secondary_y3 - player_ancor_y};
            Vector2 ttpa = {player[player_id].x + ((triangle_third_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_third_y1 - player_ancor_y};
            Vector2 ttpb = {player[player_id].x + ((triangle_third_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_third_y2 - player_ancor_y};
            Vector2 ttpc = {player[player_id].x + ((triangle_third_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_third_y3 - player_ancor_y};
            Vector2 tfpa = {player[player_id].x + ((triangle_fourth_x1  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_fourth_y1 - player_ancor_y};
            Vector2 tfpb = {player[player_id].x + ((triangle_fourth_x2  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_fourth_y2 - player_ancor_y};
            Vector2 tfpc = {player[player_id].x + ((triangle_fourth_x3  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + triangle_fourth_y3 - player_ancor_y};
            
            /// Circle Eye Point
            Vector2 cep = {player[player_id].x + ((circle_eye_x  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + circle_eye_y - player_ancor_y};
            
            /// Square Head Point|Size
            Vector2 shp = {player[player_id].x + ((square_head_x  - player_ancor_x) * BOOL_SIGN(player[player_id].sign)), player[player_id].y + square_head_y - player_ancor_y};
            Vector2 shs = {8, 12};

            // force clock-wise triangle | fix rectangle pos
            if (player[player_id].sign == SIDE_LEFT) {
                // triangle primary
                aux_v = tppb;
                tppb = tppc;
                tppc = aux_v;
                // triangle secondary
                aux_v = tspb;
                tspb = tspc;
                tspc = aux_v;
                // triangle third
                aux_v = ttpb;
                ttpb = ttpc;
                ttpc = aux_v;
                // triangle fourth
                aux_v = tfpb;
                tfpb = tfpc;
                tfpc = aux_v;

                //-----------------------------------//
                // rectangle pos
                shp.x -= shs.x;
            }

            /// Render In Shape
            DrawTriangle(tppa, tppb, tppc, color_inshape);
            DrawTriangle(tspa, tspb, tspc, color_inshape);
            DrawTriangle(ttpa, ttpb, ttpc, color_inshape);
            DrawTriangle(tfpa, tfpb, tfpc, ORANGE);
            DrawRectangleV(shp, shs, color_inshape);

            DrawTriangleLines(tppa, tppb, tppc, color_outline);
            DrawTriangleLines(tspa, tspb, tspc, color_outline);
            DrawTriangleLines(ttpa, ttpb, ttpc, color_outline);
            DrawTriangleLines(tfpa, tfpb, tfpc, color_outline);
            DrawRectangleLines(shp.x, shp.y, shs.x, shs.y, color_outline);
            DrawCircleV(cep, 2, BLACK);
            break;
        }
    }
}

void PlayerStep(player_t player_id)
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

player_t PlayerNear(player_t not_player_id, float x, float y)
{
    float distance_old = 0xFFFFFF;
    float distance_new = 0x00;
    player_t nearest = 0; 

    for (player_t player_near = 0; player_near < MAX_PLAYERS; player_near++) {
        
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

float PlayerDistance(player_t player_a, player_t player_b)
{
    return PointDistance2D(player[player_a].x, player[player_a].y, player[player_b].x, player[player_b].y);
}

void PlayerMediatorStep(void)
{
    for (player_t i = 0; i < MAX_PLAYERS; i++) {
        if (player[i].state != fsm_player_atck) {
            continue;
        }
        
        for (player_t j = 0; j < MAX_PLAYERS; j++) {

            if (player[j].state == fsm_player_atck || player[j].state == fsm_player_died) {
                continue;
            }

            if (PlayerDistance(i, j) < PLAYER_SIZE) {
                player[j].state = fsm_player_died;
            }
        }
    }
}

bool PlayerDeath(player_t player_id)
{
    return player[player_id].state == fsm_player_died;
}

Vector2 PlayerPos(player_t player_id)
{
    Vector2 pos = {player[player_id].x, player[player_id].y};
    return pos;
}

player_t PlayerCount()
{
    return players_count;
}

void PlayerCountStep()
{
    players_count = 0;

    for (
        player_t i = 0; i < PLAYER_SIZE;
        players_count += (player_t) (player[i].state != fsm_player_died), i++
    );
}