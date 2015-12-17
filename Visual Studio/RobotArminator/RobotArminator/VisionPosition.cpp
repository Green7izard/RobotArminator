#include "stdafx.h"
#include "VisionPosition.hpp"

namespace RobotArminator
{

    VisionPosition::VisionPosition()
    {
		isDefault = true;
    }

    VisionPosition::VisionPosition(double X, double Y, Time time, Orientation orientation)
        : X(X), Y(Y), time(time), orientation(orientation)
    {
		isDefault = false;
    }


    VisionPosition::~VisionPosition()
    {
    }
}