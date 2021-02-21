#pragma once

#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <raymath.h>
#include <time.h>
#include <time.h>


#define GAME_TITLE                      "Coco Battle Royale 2"
#define GAME_AWAIT                      (5)
#define GAME_FPS                        (60)
#define DEFAULT_SCREEN_WIDTH            (800)
#define DEFAULT_SCREEN_HEIGHT           (600)
#define MAX_PLAYERS                     (16)
#define PLAYER_ATTACK_TIME              (10)
#define PLAYER_RECOVERY_TIME            (15)
#define PLAYER_COMBO_TIME               (30)
#define PLAYER_ANY                      (-1)
#define PLAYER_AWAY                     (2)
#define PLAYER_SIZE                     (48)
#define PLAYER_MAX_SPEED                (480)
#define PLAYER_INC_SPEED                (0.24)
#define WORD_LIMIT_X                    (DEFAULT_SCREEN_WIDTH-PLAYER_SIZE-1)
#define WORD_LIMIT_Y                    (DEFAULT_SCREEN_HEIGHT-PLAYER_SIZE-1)
#define irand(limit)                    GetRandomValue(0,limit)
#define PointDistance2D(x1,y1,x2,y2)    sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)))
#define SIDE_RANDOM                     (GetRandomValue(0,1)?-1:1)
#define SIDE_LEFT                       -1
#define SIDE_RIGHT                      1

#if MAX_PLAYERS < 256
typedef unsigned char player_t;
#endif
#if MAX_PLAYERS > 255 && MAX_PLAYERS < 65536
typedef unsigned int player_t;
#endif
#if MAX_PLAYERS > 65535 && MAX_PLAYERS < 4294967296
typedef unsigned long player_t;
#endif

typedef unsigned char state_t;
typedef signed char axis_i_t;
typedef signed char Axis;
typedef unsigned char ColorId;
typedef unsigned long int Tick;

// FILE: main.c
Tick GameStep(void);
bool IsGameStarted(void);

// FILE: color.c
Color ColorPlayer(void);
Color ColorBackgroundId(bool reset);
Color ColorGet(ColorId color_id);

// FILE: ia_bot.c
void BotIaInit(player_t player_id);
void BotIaStep(player_t player_id);
void BotIaChange(player_t player_id);
void BotIaRetarget(player_t player_id);
bool BotAttack(player_t player_id);
int BotAxisX(player_t player_id);
int BotAxisY(player_t player_id);

// FILE: input.c
void InputStep(void);
int InputAxisX(void);
int InputAxisY(void);
bool inputAttack(void);

// FILE: player.c
void PlayerMediatorStep(void);
void PlayerInit(player_t player_id);
void PlayerDraw(player_t player_id);
void PlayerStep(player_t player_id);
bool PlayerDeath(player_t player_id);
float PlayerDistance(player_t player_a, player_t player_b);
player_t PlayerNear(player_t not_player_id, float x, float y);
Vector2 PlayerPos(player_t player_id);
player_t PlayerCount(void);
void PlayerCountStep(void);