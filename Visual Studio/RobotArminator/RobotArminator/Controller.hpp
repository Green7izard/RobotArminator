#pragma once
#include "stdafx.h"
#include "IBallPositionCalculator.hpp"
#include "IComputerVision.hpp"
#include "IRobotControl.hpp"
#include "Camera.hpp"

namespace RobotArminator
{
    using namespace BallPosition;
    using namespace Vision;
    using namespace Robot;

    class Controller
    {
    public:
        Controller(double tableLength = DEFAULT_LENGTH, double tableWidth = DEFAULT_WIDTH);
        ~Controller();
    private:
        IBallPositionCalculator *ballPostionCalculator;
        IComputerVision *computerVisionTop;
        IComputerVision *computerVisionSide;
        IRobotControl *robotControl;
        Camera *top;
        Camera *side;

    };
}

