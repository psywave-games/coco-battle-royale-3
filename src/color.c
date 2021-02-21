#include "header.h"

static ColorId background_color;

Color ColorPlayer()
{
    ColorId player_color;

    do {
        player_color = GetRandomValue(1,5);
    }
    while (player_color == background_color);
    
    return ColorGet(player_color + 5);
}

Color ColorBackground(bool reset)
{
    if (reset) {
        background_color = GetRandomValue(1, 5);
    }  

    return ColorGet(background_color);
}

Color ColorGet(ColorId color_id)
{
    switch (color_id) {
        case 1: return MAROON;
        case 2: return DARKGREEN;
        case 3: return DARKBLUE;
        case 4: return DARKPURPLE;
        case 5: return DARKBROWN;
        case 6: return PINK;
        case 7: return GREEN;
        case 8: return SKYBLUE;
        case 9: return PURPLE;
        case 10: return BEIGE;
        default: return BLACK;
    }
}