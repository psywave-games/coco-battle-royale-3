#pragma once
#define GAME_TITLE                      "Coco Battle Royale 2"
#define DEFAULT_SCREEN_WIDTH            (800)
#define DEFAULT_SCREEN_HEIGHT           (600)
#define MAX_PLAYERS                     (16)
#define PLAYER_ATTACK_TIME              (1)
#define PLAYER_ANY                      (-1)
#define PLAYER_AWAY                     (2)
#define PLAYER_SIZE                     (48)
#define PLAYER_MAX_SPEED                (650)
#define PLAYER_INC_SPEED                (0.96)
#define WORD_LIMIT_X                    (DEFAULT_SCREEN_WIDTH-PLAYER_SIZE-1)
#define WORD_LIMIT_Y                    (DEFAULT_SCREEN_HEIGHT-PLAYER_SIZE-1)
#define irand(limit)                    GetRandomValue(0,limit)
#define PointDistance2D(x1,y1,x2,y2)    sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)))
#define BOOL_SIGN(sign)                 (sign?1:-1) 
#define UNIX_TIME                       time(NULL)
#define SIDE_LEFT                       false
#define SIDE_RIGHT                      true

typedef unsigned char player_t;
typedef unsigned char state_t;
typedef signed char axis_i_t;
typedef bool axis_b_t;

// FILE: ia_bot.c
void BotIaInit(player_t player_id);
void BotIaStep(void);
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
