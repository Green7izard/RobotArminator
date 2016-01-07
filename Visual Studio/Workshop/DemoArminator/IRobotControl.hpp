#pragma once

#include "stdafx.h"
#include "Thread.hpp"
#include "Trajectory.hpp"
#include <iostream>

namespace Robot
{
    using namespace RobotArminator;

    class IRobotControl : public Thread
    {
    public:
        virtual ~IRobotControl() = 0;
        virtual void moveArm(Trajectory aTrajectory) = 0;
        virtual void resetPositions() = 0;
        virtual void writeData(std::string aData) = 0;
        virtual std::string readData() = 0;
    protected:
        IRobotControl();
    };
    inline IRobotControl::IRobotControl() {};
    inline IRobotControl::~IRobotControl() {};
}