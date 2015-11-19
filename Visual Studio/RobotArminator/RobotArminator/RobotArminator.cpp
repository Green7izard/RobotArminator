// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "Controller.hpp"
#include "BallPositionCalculator.hpp"
#include "VisionPosition.hpp"

using namespace RobotArminator;

int main(int argc, char* argv[])
{
	BallPositionCalculator ballPositionCalculator;
	RobotArminator::VisionPosition visionPositionSideView = { 1000, 200, time_t(0.1), UP };
	RobotArminator::VisionPosition visionPositionTopView = { 1000, 300, time_t(0.1), SIDE };

	ballPositionCalculator.startPositionCalculation();
	ballPositionCalculator.calculateTwoPositionToOnePosition(visionPositionSideView, visionPositionTopView);

	//wait for input
	std::cin.get();    
	
	return 0;
}

