#pragma once

#include "Vector.hpp"

namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl
    {
    public:
        virtual ~IRobotControl()=0;
        virtual void moveArm(Vector position)=0;
        virtual Vector getPosition()=0;
        virtual void hitBall(Vector position)=0;
    protected:
        IRobotControl();
    };

}