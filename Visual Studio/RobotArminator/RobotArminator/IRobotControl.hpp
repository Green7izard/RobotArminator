#pragma once
#include "stdafx.h"
#include "Vector.hpp"
#include "Thread.hpp"
namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl : public Thread
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