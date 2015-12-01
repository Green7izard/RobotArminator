#pragma once
#include "stdafx.h"
#include "Orientation.hpp"

namespace RobotArminator
{
    using namespace std;

    struct VisionPosition
    {
    public:
        VisionPosition();
        VisionPosition(float X, float Y, timePoint time, Orientation orientation);
        ~VisionPosition();
        float X;
        float Y;
        timePoint time;
        Orientation orientation;
    };
}
