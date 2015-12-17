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
        VisionPosition(double X, double Y, Time time, Orientation orientation);
        ~VisionPosition();
		bool isDefault;
		double X;
		double Y;
        Time time;
        Orientation orientation;
    };
}
