#pragma once
#include "stdafx.h"
#include "VisionPosition.hpp"
#include "Trajectory.hpp"
#include "Thread.hpp"
#include "IMessageBox.hpp"

namespace BallPosition
{
    using namespace RobotArminator;

    class IBallPositionCalculator : public Thread, public IMessageBox
    {
    public:
        IBallPositionCalculator();
        virtual ~IBallPositionCalculator();

    };

}