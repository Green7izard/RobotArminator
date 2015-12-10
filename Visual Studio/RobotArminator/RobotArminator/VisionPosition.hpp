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
        VisionPosition(float X, float Y, Time time, Orientation orientation);
        ~VisionPosition();
		bool isDefault;
        float X;
        float Y;
        Time time;
        Orientation orientation;
    };
}
