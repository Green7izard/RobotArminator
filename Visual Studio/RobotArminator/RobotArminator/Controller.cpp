#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"
#include "PFCVision.hpp"
namespace RobotArminator
{

    Controller::Controller(double tableLength, double tableWidth)
    {
        std::cout << "Constructing" << std::endl;
        robotControl = new RobotControl("COM4", 19200);
        ballPostionCalculator = new BallPositionCalculator(tableLength, robotControl);

        top = new Camera(1);
        side = new Camera(0);
        std::cout << "Starting Visions" << std::endl;
        computerVisionTop = new PFCVision(Orientation::TOP, top, tableLength, tableWidth);
        computerVisionSide = new PFCVision(Orientation::SIDE, side, tableLength, tableWidth);
        computerVisionTop->addListener(ballPostionCalculator);
        computerVisionSide->addListener(ballPostionCalculator);

        std::cout << "starting threads" << std::endl;
        ballPostionCalculator->start();
        computerVisionTop->start();
        computerVisionSide->start();

    }


    Controller::~Controller()
    {
        std::cout << "ending threads" << std::endl;
        ballPostionCalculator->stop();
        computerVisionTop->stop();
        computerVisionSide->stop();

        delete(ballPostionCalculator);
        delete(computerVisionTop);
        delete(computerVisionSide);
    }
}