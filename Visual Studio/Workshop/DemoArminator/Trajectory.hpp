#pragma once
#include "stdafx.h"
#include "Vector.hpp"

namespace RobotArminator
{
    struct Trajectory
    {
    public:
        Trajectory();
		Trajectory(Vector position);
        ~Trajectory();
        Vector position;
    };
}
