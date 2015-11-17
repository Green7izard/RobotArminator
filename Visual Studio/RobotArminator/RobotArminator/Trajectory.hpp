#pragma once
#include "Vector.hpp"
#include <ctime>
namespace RobotArminator
{
    struct Trajectory
    {
    public:
        Trajectory();
		Trajectory(Vector position, Vector speed, time_t time);
        ~Trajectory();
        Vector position;
        Vector speed;
		std::time_t time;
    };
}
