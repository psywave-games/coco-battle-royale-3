#include "header.h"

static ColorId background_color;

Color ColorPlayer()
{
    ColorId player_color;

    do {
        player_color = GetRandomValue(1,6);
    }
    while (player_color == background_color);
    
    return ColorGet(player_color + 6);
}

Color ColorBackground(bool reset)
{
    if (reset) {
        background_color = GetRandomValue(1, 6);
    }  

    return ColorGet(background_color);
}

Color ColorGet(ColorId color_id)
{
    switch (color_id) {
        case 1: return MAROON; 
        case 2: return ORANGE;
        case 3: return DARKGREEN;
        case 4: return DARKBLUE;
        case 5: return DARKPURPLE;
        case 6: return DARKBROWN;
        case 7: return PINK;
        case 8: return YELLOW;
        case 9: return GREEN;
        case 10: return SKYBLUE;
        case 11: return PURPLE;
        case 12: return BEIGE;
        default: return BLACK;
    }
}