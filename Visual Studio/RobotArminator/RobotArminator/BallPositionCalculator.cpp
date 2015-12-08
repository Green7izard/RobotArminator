#include <iostream>
#include <math.h>
#include "BallPositionCalculator.hpp"
#include "Trajectory.hpp"
#include "Vector.hpp"

namespace BallPosition
{

	using namespace RobotArminator;

	BallPositionCalculator::BallPositionCalculator()
	{
	}


	BallPositionCalculator::~BallPositionCalculator()
	{
	}

	//run thread
	void BallPositionCalculator::run()
	{
	}

	//start threadfunction
	void BallPositionCalculator::startPositionCalculation()
	{
	}

	VisionPosition BallPositionCalculator::getPositionsFromQueue()
	{
		currentTopPosition = VisionPosition();
		return currentTopPosition;
	}

	Position BallPositionCalculator::calculateHitPosition(VisionPosition newSideView, VisionPosition newTopView)
	{
		float yValue = calculateLiniairPosition(newTopView); // Y Coordinate of the top-view when reaching the end of the table.

		std::cout << "New Time: " << newSideView.time << " And old Time: " << std::endl;//oldSideView.time << std::endl;
		abcCalculator.setFormule(newSideView, lastSidePosition, newSideView.X, true);
		float tempXValue = abcCalculator.getLargestXPosition(0);
		float tempYValue = abcCalculator.getYPosition((tempXValue - 1));
		float time = 0;

		std::cout << "From top-coordinates (" << lastTopPosition.X << "," << lastTopPosition.Y << ") to (" << newTopView.X << "," << newTopView.Y << ")" << std::endl;
		std::cout << "From side-coordinates (" << lastSidePosition.X << "," << lastSidePosition.Y << ") to (" << newSideView.X << "," << newSideView.Y << ")" << std::endl;

		//Get Time and Length
		time += abcCalculator.getTime(0, tempXValue);

		/*
		TODO SET TIME!
		*/
		abcCalculator.setFormule(VisionPosition((tempXValue + 1), tempYValue, Clock::universal_time(), SIDE), VisionPosition(tempXValue, 0, Clock::universal_time(), SIDE), tempXValue, false);
		float zValue = abcCalculator.getYPosition(tableWidth);

		//Get Time and Length
		time += abcCalculator.getTime(tempXValue + 1, tableWidth);
		std::cout << "Time: " << time << " Milliseconds" << std::endl;

		std::cout << "( tableWidth , tableDepth , Height )." << std::endl;
		std::cout << "Hit the table at: ("<< tableWidth << "," << yValue << "," << zValue << ")." << std::endl;
		Position p = Position(Vector(tableWidth, yValue, zValue), 0);
		return p;
	}

	float BallPositionCalculator::calculateLiniairPosition(VisionPosition pos)
	{
		float multiplier = (pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		float startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		float newY = (multiplier * tableWidth) + startValue;
		return newY;
	}

	void BallPositionCalculator::sendPosition()
	{
	}

}