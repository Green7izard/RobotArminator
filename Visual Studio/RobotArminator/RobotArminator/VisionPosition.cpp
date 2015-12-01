#include "stdafx.h"
#include "VisionPosition.hpp"

namespace RobotArminator
{

    VisionPosition::VisionPosition()
    {
    }

    VisionPosition::VisionPosition(float X, float Y, timePoint, Orientation orientation)
        : X(X), Y(Y), time(time), orientation(orientation)
    {
    }


    VisionPosition::~VisionPosition()
    {
    }
}