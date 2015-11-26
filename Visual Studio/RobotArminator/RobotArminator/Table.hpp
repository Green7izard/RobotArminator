#pragma once


namespace Vision
{
    /**
    * Specifies a corner location in the image
    */
    struct Position2D { unsigned int X; unsigned int Y; };
    /**
    * Specifies a table defined by its corners
    */
    struct Table {
        Position2D TopLeft; Position2D TopRight;
        Position2D BotLeft; Position2D BotRight;
    };
}