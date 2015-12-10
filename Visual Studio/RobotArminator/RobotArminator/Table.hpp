#pragma once
#include "stdafx.h"

namespace Vision
{
    /**
    * Specifies a corner location in the image
    */
    struct Position2D { int X =-1; int Y =-1; };
    /**
    * Specifies a table defined by its corners
    */
    struct Table {
        Position2D TopLeft; Position2D TopRight;
        Position2D BotLeft; Position2D BotRight;
    };
}