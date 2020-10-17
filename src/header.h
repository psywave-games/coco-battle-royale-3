#pragma once
#define GAME_TITLE                  "Coco Battle Royale 2"
#define DEFAULT_SCREEN_WIDTH            (800)
#define DEFAULT_SCREEN_HEIGHT           (600)
#define MAX_PLAYERS                     (32)
#define PLAYER_ANY                      (-1)
#define PLAYER_AWAY                     (12)
#define PLAYER_SIZE                     (32)
#define PLAYER_MAX_SPEED                (500)
#define PLAYER_INC_SPEED                (0.96)
#define WORD_LIMIT_X                    (DEFAULT_SCREEN_WIDTH-PLAYER_SIZE-1)
#define WORD_LIMIT_Y                    (DEFAULT_SCREEN_HEIGHT-PLAYER_SIZE-1)
#define PointDistance2DF(x1,y1,x2,y2)    sqrtf((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))
#define PointDistance2DI(x1,y1,x2,y2)    sqrt((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1))

void InputStep();
int InputAxisX();
int InputAxisY();

void PlayerInit(char player_id);
void PlayerDraw(char player_id);
void PlayerStep(char player_id);
char PlayerNear(char not_player_id, float x, float y);
float PlayerDistance(char player_a, char player_b);