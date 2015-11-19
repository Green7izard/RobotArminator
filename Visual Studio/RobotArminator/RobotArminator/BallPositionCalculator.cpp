#include <iostream>
#include "BallPositionCalculator.hpp"
#include "Trajectory.hpp"
#include "Vector.hpp"

using namespace RobotArminator;

//run thread
void BallPositionCalculator::run()
{
}

//start threadfunction
void BallPositionCalculator::startPositionCalculation()
{
	std::cout << "Start!" << std::endl;
}


VisionPosition BallPositionCalculator::getPositionsFromQueue()
{
	currentPosition = VisionPosition();
	return currentPosition;
}


void BallPositionCalculator::calculateTwoPositionToOnePosition(VisionPosition sideView, VisionPosition topView)
{
	float time;
	if(sideView.time >= topView.time)
	{
		time = sideView.time;
	}
	else
	{
		time = topView.time;
	}
	Trajectory newTraject(time, Vector(0, 0, 0), Vector(topView.X, topView.Y, sideView.Y));
	std::cout << "X: " << newTraject.position.x << "mm and Y: " << newTraject.position.y << "mm and Z: " << newTraject.position.z << "mm and Time: " << newTraject.time << "ms";
}


void BallPositionCalculator::sendPosition()
{
}


BallPositionCalculator::BallPositionCalculator()
{
}


BallPositionCalculator::~BallPositionCalculator()
{
}