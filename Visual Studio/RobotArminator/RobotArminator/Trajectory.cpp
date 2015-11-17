#include "stdafx.h"
#include "Trajectory.hpp"

namespace RobotArminator
{
    Trajectory::Trajectory()
    {
    }

	Trajectory::Trajectory(Vector position, Vector speed, time_t time) :position(position), speed(speed), time(time) {

	}


    Trajectory::~Trajectory()
    {
    }
}