#pragma once
#include "Vector.hpp"
namespace RobotArminator
{
    struct Trajectory
    {
    public:
        Trajectory();
        ~Trajectory();
        Vector position;
        Vector speed;
    };
}
