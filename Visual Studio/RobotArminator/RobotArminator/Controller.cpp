#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"

namespace RobotArminator
{

    Controller::Controller()
    {
        ballPostionCalculator = new BallPositionCalculator();
        ballPostionCalculator->start();


        ballPostionCalculator->stop();
        delete(ballPostionCalculator);
    }


    Controller::~Controller()
    {
    }
}