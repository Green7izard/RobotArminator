#pragma once
#include <ctime>
#include "Orientation.hpp"

namespace RobotArminator
{
    struct VisionPosition
    {
    public:
        VisionPosition();
        VisionPosition(float X, float Y, std::time_t time, Orientation orientation);
        ~VisionPosition();
        float X;
        float Y;
        std::time_t time;
        Orientation orientation;
    };
}
