// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"

using namespace RobotArminator;
using namespace BallPosition;

int main(int argc, char* argv[])
{
	BallPositionCalculator ballPositionCalculator;
	VisionPosition visionPositionSideView = { 2000, 200, std::time_t(4.9), SIDE };
	VisionPosition visionPositionTopView = { 2000, 500, std::time_t(4.9), TOP };

	ballPositionCalculator.startPositionCalculation();
	ballPositionCalculator.calculateTraject(visionPositionSideView, visionPositionTopView);

	//wait for input
	std::cin.get(); 
    //Controller controller;
    return 0;
}

