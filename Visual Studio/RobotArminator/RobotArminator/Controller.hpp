#pragma once
#include "stdafx.h"
#include "IBallPositionCalculator.hpp"
#include "IComputerVision.hpp"
#include "IRobotControl.hpp"

namespace RobotArminator
{
    using namespace BallPosition;
    using namespace Vision;
    using namespace Robot;

    class Controller
    {
    public:
        Controller();
        ~Controller();
    private:
        IBallPositionCalculator *ballPostionCalculator;
        IComputerVision *computerVision;
        IRobotControl *robotControl;


    };
}

