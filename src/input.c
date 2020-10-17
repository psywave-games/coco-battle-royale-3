#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include "header.h"

static signed char atual_axis_x = 0;
static signed char atual_axis_y = 0;

void InputStep()
{
    atual_axis_y = ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)));
    atual_axis_x = ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));
}

int InputAxisX()
{
    return (int) atual_axis_x;
}
    
int InputAxisY()
{
    return (int) atual_axis_y;
}