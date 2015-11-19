#pragma once

#include "Vector.hpp"

namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl
    {
    public:
        IRobotControl();
        virtual ~IRobotControl();
        virtual void moveArm(Vector position);
        virtual Vector getPosition();
        virtual void hitBall(Vector position);
    };

}