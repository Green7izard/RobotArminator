#include "stdafx.h"
#include "Trajectory.hpp"

namespace RobotArminator
{
    Trajectory::Trajectory()
    {
    }

	Trajectory::Trajectory(Vector position, Time time) :position(position), time(time) {

	}


    Trajectory::~Trajectory()
    {
    }
}