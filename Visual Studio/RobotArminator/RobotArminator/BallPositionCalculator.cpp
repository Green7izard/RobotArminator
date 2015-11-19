#include <iostream>
#include "BallPositionCalculator.hpp"
#include "Trajectory.hpp"
#include "Vector.hpp"

namespace BallPosition
{

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
		currentTopPosition = VisionPosition();
		return currentTopPosition;
	}


	void BallPositionCalculator::calculateTraject(VisionPosition sideView, VisionPosition topView)
	{
		calculateLiniairTraject(topView);
	}

	void BallPositionCalculator::calculateLiniairTraject(VisionPosition pos)
	{
		float multiplier = (float)(pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		int startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		int newY = (multiplier * 2740) + startValue;
		std::cout << multiplier << " * " << "2740" << " + " << startValue << " = " << newY << std::endl;

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
}