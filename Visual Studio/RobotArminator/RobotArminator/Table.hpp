#pragma once


namespace ComputerVision
{
    /**
    * Specifies a corner location in the image
    */
    struct Corner { unsigned int X; unsigned int Y; };
    /**
    * Specifies a table defined by its corners
    */
    struct Table {
        Corner TopLeft; Corner TopRight;
        Corner BotLeft; Corner BotRight;
    };
}