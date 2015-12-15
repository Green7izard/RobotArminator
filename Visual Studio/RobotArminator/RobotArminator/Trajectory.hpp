#pragma once
#include "stdafx.h"
#include "Vector.hpp"

namespace RobotArminator
{
    struct Trajectory
    {
    public:
        Trajectory();
		Trajectory(Vector position, Time time);
        ~Trajectory();
        Vector position;
		Time time;
    };
}
