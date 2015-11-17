#include "stdafx.h"
#include "Position.hpp"

RobotArminator::Position::Position()
{
}

RobotArminator::Position::Position(double x, double y, double z, int rotation) :
    Vector(x,y,z), rotation(rotation)
{
}

RobotArminator::Position::~Position()
{
}
