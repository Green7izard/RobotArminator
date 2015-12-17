#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"
#include "PFCVision.hpp"
namespace RobotArminator
{

    Controller::Controller()
    {
        std::cout << "Constructing" << std::endl;
        ballPostionCalculator = new BallPositionCalculator();
        
        top = new Camera(1);
        side = new Camera(0);
        std::cout << "Starting Visions" << std::endl;
        computerVisionTop = new PFCVision(Orientation::TOP, top);
        computerVisionSide = new PFCVision(Orientation::SIDE, side);
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