// RobotArminator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"
#include <chrono>
#include <iostream>
#include <ctime>
using namespace RobotArminator;
using namespace BallPosition;

int main(int argc, char* argv[])
{
	BallPositionCalculator ballPositionCalculator;

	VisionPosition visionPositionSideView (2000, 200, Clock::universal_time() + boost::posix_time::milliseconds(60), SIDE );
	VisionPosition visionPositionTopView (2000, 500, Clock::universal_time() + boost::posix_time::milliseconds(60), TOP );


	VisionPosition lastSidePosition (1750, 300, Clock::universal_time() + boost::posix_time::milliseconds(10), SIDE);
	VisionPosition lastTopPosition (1750, 400, Clock::universal_time() + boost::posix_time::milliseconds(10), TOP);

	ballPositionCalculator.startPositionCalculation();
	ballPositionCalculator.calculateHitPosition(lastSidePosition, lastTopPosition);
	ballPositionCalculator.calculateHitPosition(visionPositionSideView, visionPositionTopView);

	//wait for input
	std::cin.get(); 
    //Controller controller;
    return 0;
}

