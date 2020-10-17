#pragma once
#define GAME_TITLE                  "Coco Battle Royale 2"
#define DEFAULT_SCREEN_WIDTH            (800)
#define DEFAULT_SCREEN_HEIGHT           (600)
#define MAX_PLAYERS                     (32)
#define PLAYER_ATTACK_TIME              (1)
#define PLAYER_ANY                      (-1)
#define PLAYER_AWAY                     (3)
#define PLAYER_SIZE                     (24)
#define PLAYER_MAX_SPEED                (500)
#define PLAYER_INC_SPEED                (0.96)
#define WORD_LIMIT_X                    (DEFAULT_SCREEN_WIDTH-PLAYER_SIZE-1)
#define WORD_LIMIT_Y                    (DEFAULT_SCREEN_HEIGHT-PLAYER_SIZE-1)
#define irand(limit)                    GetRandomValue(0,limit)
#define PointDistance2D(x1,y1,x2,y2)    sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)))
#define BOOL_SIGN(sign)                 (sign?1:-1) 
#define UNIX_TIME                       time(NULL)
#define SIDE_LEFT                       false
#define SIDE_RIGHT                      true

// FILE: ia_bot.c
void BotIaInit(char player_id);
void BotIaStep(void);
void BotIaChange(char player_id);
void BotIaRetarget(char player_id);
bool BotAttack(char player_id);
int BotAxisX(char player_id);
int BotAxisY(char player_id);

// FILE: input.c
void InputStep(void);
int InputAxisX(void);
int InputAxisY(void);
bool inputAttack(void);

// FILE: player.c
void PlayerInit(char player_id);
void PlayerDraw(char player_id);
void PlayerStep(char player_id);
void PlayerMediatorStep(void);
char PlayerNear(char not_player_id, float x, float y);
float PlayerDistance(char player_a, char player_b);
bool PlayerDeath(char player_id);
Vector2 PlayerPos(char player_id);
