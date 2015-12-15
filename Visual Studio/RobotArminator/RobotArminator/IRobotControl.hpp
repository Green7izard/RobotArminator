#pragma once

#include "stdafx.h"
#include "Trajectory.hpp"
#include <iostream>
#include "Thread.hpp"

namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl : public Thread
    {
    public:
        virtual ~IRobotControl()=0;
        virtual void moveArm(Trajectory aTrajectory)=0;
        virtual void hitBall(Trajectory aTrajectory)=0;
    protected:
        IRobotControl();
    };
    inline IRobotControl::IRobotControl() {};
    inline IRobotControl::~IRobotControl() {};
}