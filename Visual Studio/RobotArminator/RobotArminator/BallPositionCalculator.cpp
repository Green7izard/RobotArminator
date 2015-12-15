#include "stdafx.h"
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
		std::cout << "Start run" << std::endl;
		while (running)
		{
			if (!queueSidePosition.isDefault && !queueTopPosition.isDefault)
			{
				std::cout << "Start Calculator" << std::endl;
				getPositionsFromQueue();
				calculateHitPosition();
			}
		}
	}

	void BallPositionCalculator::addToMessageBox(VisionPosition item)
	{
		if (item.orientation == Orientation::SIDE)
		{
			queueSidePosition = item;
		}
		else if (item.orientation == Orientation::TOP)
		{
			queueTopPosition = item;
		}
	}

	void BallPositionCalculator::getPositionsFromQueue()
	{
		currentSidePosition = queueSidePosition;
		queueSidePosition = VisionPosition();
		currentTopPosition = queueTopPosition;
		queueTopPosition = VisionPosition();
	}

	Trajectory BallPositionCalculator::calculateHitPosition()
	{
		float yValue;
		Trajectory t;
		if (!lastTopPosition.isDefault)
		{
			yValue = calculateLiniairPosition(currentTopPosition); // Y Coordinate of the top-view when reaching the end of the table.
			std::cout << "From top-coordinates (" << lastTopPosition.X << "," << lastTopPosition.Y << ") to (" << currentTopPosition.X << "," << currentTopPosition.Y << ")" << std::endl;
		}

		lastTopPosition = currentTopPosition;

		if(!lastSidePosition.isDefault)
		{
			abcCalculator.setFormule(currentSidePosition, lastSidePosition, currentSidePosition.X, true);
			float tempXValue = abcCalculator.getLargestXPosition(0);
			float tempYValue = abcCalculator.getYPosition((tempXValue - 1));
			float time = 0;

			std::cout << "From side-coordinates (" << lastSidePosition.X << "," << lastSidePosition.Y << ") to (" << currentSidePosition.X << "," << currentSidePosition.Y << ")" << std::endl;

			//Get Time and Length
			time += abcCalculator.getTime(lastSidePosition.X, tempXValue);

			abcCalculator.setFormule(VisionPosition((tempXValue + 1), tempYValue, Clock::universal_time(), SIDE), VisionPosition(tempXValue, 0, Clock::universal_time(), SIDE), tempXValue, false);
			float zValue = abcCalculator.getYPosition(tableWidth + 100);

			//Get Time and Length
			time += abcCalculator.getTime(tempXValue + 1, tableWidth + 100);
			std::cout << "Time: " << time << " Milliseconds" << std::endl;

			std::cout << "( tableWidth , tableDepth , Height )." << std::endl;
			std::cout << "Hit the table at: ("<< tableWidth << "," << yValue << "," << zValue << ")." << std::endl;
			t = Trajectory(Vector(tableWidth, yValue, zValue), Clock::universal_time() + boost::posix_time::milliseconds(time));
		}
		lastSidePosition = currentSidePosition;
		return t;
	}

	float BallPositionCalculator::calculateLiniairPosition(VisionPosition pos)
	{
		float multiplier = (pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		float startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		float newY = (multiplier * (tableWidth + 100)) + startValue;
		return newY;
	}

	void BallPositionCalculator::sendPosition()
	{
	}

}