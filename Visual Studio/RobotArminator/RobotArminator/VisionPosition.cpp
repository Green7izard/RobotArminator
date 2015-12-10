#include "stdafx.h"
#include "VisionPosition.hpp"

namespace RobotArminator
{

    VisionPosition::VisionPosition()
    {
		isDefault = true;
    }

    VisionPosition::VisionPosition(float X, float Y, Time time, Orientation orientation)
        : X(X), Y(Y), time(time), orientation(orientation)
    {
    }


    VisionPosition::~VisionPosition()
    {
    }
}