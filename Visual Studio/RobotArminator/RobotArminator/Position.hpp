#pragma once
#include "stdafx.h"
#include "Vector.hpp"
namespace RobotArminator
{
    struct Position : public Vector
    {
    public:
        Position();
        Position(double x, double y, double z, int rotation);
		Position(Vector vector, int rotation);
        ~Position();
        int rotation;
    };
    
}
