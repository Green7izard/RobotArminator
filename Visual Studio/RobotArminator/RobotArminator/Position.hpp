#pragma once
#include "Vector.hpp"
namespace RobotArminator
{
    struct Position : public Vector
    {
    public:
        Position();
        Position(double x, double y, double z, int rotation);
        ~Position();
        int rotation;
    };
    
}
