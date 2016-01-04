#pragma once

#include "stdafx.h"
#include "Trajectory.hpp"
#include <iostream>

namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl
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