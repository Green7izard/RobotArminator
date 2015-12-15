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
				//std::cout << "Start Calculator" << std::endl;
				getPositionsFromQueue();
				calculateHitPosition();
              //  std::cout << "End Calculator" << std::endl;
			}
		}
	}

	void BallPositionCalculator::addToMessageBox(VisionPosition item)
	{
		if (item.orientation == Orientation::SIDE)
		{
        //    std::cout << "try side lock w" << std::endl;
            sideMutex.lock();
      //      std::cout << "side lock w" << std::endl;
			queueSidePosition = item;
            sideMutex.unlock();
     //       std::cout << "side unlock w" << std::endl;
		}
		else if (item.orientation == Orientation::TOP)
		{
      //     std::cout << "try top lock w" << std::endl;
            topMutex.lock();
       //    std::cout << "top lock w" << std::endl;
			queueTopPosition = item;
            topMutex.unlock();
    //       std::cout << "top unlock w" << std::endl;
		}
	}

	void BallPositionCalculator::getPositionsFromQueue()
	{
      //  std::cout << "try side lock r" << std::endl;
        sideMutex.lock();
    //    std::cout << "side lock r" << std::endl;

		currentSidePosition = queueSidePosition;
		queueSidePosition = VisionPosition();
        sideMutex.unlock();
    //    std::cout << "side unlock r" << std::endl;

   //     std::cout << "try top lock r" << std::endl;
        topMutex.lock();
  //      std::cout << "top lock r" << std::endl;
		currentTopPosition = queueTopPosition;
		queueTopPosition = VisionPosition();
        topMutex.unlock();
 //       std::cout << "top unlock r" << std::endl;
        
	}

	Trajectory BallPositionCalculator::calculateHitPosition()
	{
		double yValue;
		Trajectory t;

        if (lastSidePosition.X < currentSidePosition.X && lastTopPosition.X < currentTopPosition.X)
        {
            yValue = calculateLiniairPosition(currentTopPosition); // Y Coordinate of the top-view when reaching the end of the table.
            std::cout << "From top-coordinates (" << lastTopPosition.X << "," << lastTopPosition.Y << ") to (" << currentTopPosition.X << "," << currentTopPosition.Y << ")" << std::endl;
            

            abcCalculator.setFormule(currentSidePosition, lastSidePosition, currentSidePosition.X, true);
			double tempXValue = abcCalculator.getLargestXPositionAtYIsZero();
			double tempYValue = abcCalculator.getYPosition((tempXValue - 1));
			double time = 0;

            std::cout << "From side-coordinates (" << lastSidePosition.X << "," << lastSidePosition.Y << ") to (" << currentSidePosition.X << "," << currentSidePosition.Y << ")" << std::endl;

            //Get Time and Length
            time += abcCalculator.getTime(lastSidePosition.X, tempXValue);
			double zValue = abcCalculator.getYPosition(tableWidth + 100);
			if (zValue < 0)
			{
				//   std::cout << "Time 1: " << time << " Milliseconds" << std::endl;

				abcCalculator.setFormule(VisionPosition((tempXValue + 1), tempYValue, Clock::universal_time(), SIDE), VisionPosition(tempXValue, 0, Clock::universal_time(), SIDE), tempXValue, false);
				zValue = abcCalculator.getYPosition(tableWidth + 100);
			}
         //   std::cout << "Z: " << zValue << "" << std::endl;

            if (zValue > 0)
            {
                //Get Time and Length
                time += abcCalculator.getTime(tempXValue + 1, tableWidth + 100);
              //  std::cout << "Time: " << time << " Milliseconds" << std::endl;

            //    std::cout << "( tableWidth , tableDepth , Height )." << std::endl;
                std::cout << "\tHit the table at: (" << tableWidth << "," << yValue << "," << zValue << ")." << std::endl;
                t = Trajectory(Vector(tableWidth, yValue, zValue), Clock::universal_time() + boost::posix_time::milliseconds(time));
            }
        }

		lastSidePosition = currentSidePosition;
        lastTopPosition = currentTopPosition;

		return t;
	}

	double BallPositionCalculator::calculateLiniairPosition(VisionPosition pos)
	{
		double multiplier = (pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		double startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		double newY = (multiplier * (tableWidth + 100)) + startValue;
		return newY;
	}

	void BallPositionCalculator::sendPosition()
	{
	}

}