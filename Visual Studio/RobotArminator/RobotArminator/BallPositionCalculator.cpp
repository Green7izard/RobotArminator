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


void BallPositionCalculator::calculateTraject(VisionPosition sideView, VisionPosition topView)
{
	calculateLiniairTraject(topView);
}

void BallPositionCalculator::calculateLiniairTraject(VisionPosition pos)
{

}

void BallPositionCalculator::calculateCircleTraject(VisionPosition pos)
{

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