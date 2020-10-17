#pragma once
#define GAME_TITLE                  "Coco Battle Royale 2"
#define DEFAULT_SCREEN_WIDTH        800
#define DEFAULT_SCREEN_HEIGHT       600
#define MAX_PLAYERS                 32
#define PLAYER_MAX_SPEED            400
#define PLAYER_INC_SPEED            0.2

void InputStep();
int InputAxisX();
int InputAxisY();

void PlayerInit(int player_id);
void PlayerDraw(int player_id);
void PlayerStep(int player_id);