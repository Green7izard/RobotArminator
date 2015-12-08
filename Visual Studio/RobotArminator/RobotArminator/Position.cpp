#include "stdafx.h"
#include "Position.hpp"

namespace RobotArminator
{

    RobotArminator::Position::Position()
    {
    }

    RobotArminator::Position::Position(double x, double y, double z, int rotation) :
        Vector(x, y, z), rotation(rotation)
    {
    }

	RobotArminator::Position::Position(Vector vector, int rotation) :
		Vector(vector), rotation(rotation)
	{
	}

    RobotArminator::Position::~Position()
    {
    }
}