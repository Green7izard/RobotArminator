#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "BallPositionCalculator.hpp"
#include "Trajectory.hpp"
#include "Vector.hpp"

namespace BallPosition
{

	using namespace RobotArminator;

	BallPositionCalculator::BallPositionCalculator(double tableLength, IRobotControl* robot) : tableWidth(tableLength), robotControl(robot)
	{

	}

	BallPositionCalculator::~BallPositionCalculator()
	{
	}

    double BallPositionCalculator::TimeBeforeTableEnd(double startX, double speedX, double startTime)
    {
        double distance = tableWidth - startX;
        return startTime + distance / (speedX * 1000);
    }

    double BallPositionCalculator::CalculateXSpeed(VisionPosition p1, VisionPosition p2)
    {
        std::cout << "Timex: " << ((p2.time - p1.time).total_milliseconds() / 1000.0) << std::endl;

        return (p2.X - p1.X) / ((p2.time - p1.time).total_milliseconds() / 1000.0) / 1000;
    }

    double BallPositionCalculator::CalculateYSpeed(VisionPosition p1, VisionPosition p2)
    {
        std::cout << "Timey: " << (p2.time - p1.time).total_milliseconds() / 1000.0 << std::endl;


        double add = 9.81 * ((p2.time - p1.time).total_milliseconds() / 1000.0);

        double avgSpeed = (p2.Y - p1.Y) / ((p2.time - p1.time).total_milliseconds() / 1000.0) / 1000;

        return avgSpeed + 0.5 * add;
    }

    double BallPositionCalculator::CalculateXFromTime(double start, double speed, double time)
    {
        return start + (speed * 1000) * time;

    }

    double BallPositionCalculator::CalculateTimeWhenZero(double StartHeight, double upwardSpeedInMS)
    {
        StartHeight = StartHeight / 1000;
        double A = -4.905;
        double B = upwardSpeedInMS;
        double C = StartHeight;
        double D = (B * B) - 4 * A * C;


        double E = 2 * A;
        double F = -B / E;


        double G = sqrt(D) / E;

        double output = max(F + G, F - G);

        return output; //seconden
    }

    double BallPositionCalculator::CalculateYSpeed(double currentSpeed, double time)
    {
        return currentSpeed - 9.81 * time;
    }

    double BallPositionCalculator::CalculateHeightForT(double timeInS, double StartHeight, double upwardSpeedInMS)
    {
        return (-4.905 * (timeInS * timeInS) + upwardSpeedInMS * timeInS + StartHeight);
    }
   
    void BallPositionCalculator::calculateSide(VisionPosition p1, VisionPosition p2)
    {
        std::cout << "Side view: " << "(" << p1.X << "," << p1.Y << ")" << "(" << p2.X << "," << p2.Y << ")" << std::endl;

        if (p1.X > p2.X || p1.isDefault || p2.isDefault )
            return;

        double ySpeed = CalculateYSpeed(p1, p2);
        double xSpeed = CalculateXSpeed(p1, p2);      

        std::cout << "Speed: " << xSpeed << "," << ySpeed << std::endl;

        double hitGroundTime = CalculateTimeWhenZero(p2.Y, ySpeed);
        std::cout << "hitGroundTime: " << hitGroundTime << std::endl;

        double hitTableX = CalculateXFromTime(p2.X, xSpeed, hitGroundTime);

        if (hitTableX <= tableWidth)
        {
           /* double bounceXSpeed = xSpeed * 0.8;
            std::cout << "bounceXSpeed: " << bounceXSpeed << std::endl;

            double impactSpeed = CalculateYSpeed(ySpeed, hitGroundTime);
            double bounceYSpeed = abs(impactSpeed * 0.8);
            std::cout << "bounceYSpeed: " << bounceYSpeed << std::endl;

            double tableEndTime = TimeBeforeTableEnd(hitTableX, bounceXSpeed, hitGroundTime);
            std::cout << "tableEndTime: " << tableEndTime << std::endl;


            double tableEndY = CalculateHeightForT((tableEndTime - hitGroundTime) , 0, bounceYSpeed);
            std::cout << "tableEndY: " << tableEndY << std::endl;*/

            std::cout << "No calc" << std::endl;
        }
        else
        {
            std::cout << "geen stuit" << std::endl;
            double tableEndTime = TimeBeforeTableEnd(p2.X, xSpeed, 0);
            std::cout << "tableEndTime: " << tableEndTime << std::endl;


            double tableEndY = CalculateHeightForT(tableEndTime, p2.Y/1000.0, ySpeed) * 1000;
            std::cout << "tableEndY: " << tableEndY << std::endl;
            Time endTime = p2.time + boost::posix_time::seconds(tableEndTime);
            theTime = endTime;
            Z = tableEndY;
            updated = true;
            sideDone = true;
        }

      //  std::cout << std::endl << std::endl << std::endl << std::endl;
    }

    void BallPositionCalculator::calculateTop(VisionPosition p1, VisionPosition p2)
    {
        std::cout << "Top view: " << "(" << p1.X << "," << p1.Y << ")" << "(" << p2.X << "," << p2.Y << ")" << std::endl;


        if (p1.X > p2.X || p1.isDefault || p2.isDefault)
            return;

         double xdist = (p2.X - p1.X);
        double vspeed = (p2.Y - p1.Y) / xdist;
        double endy = p2.Y + (tableWidth - p2.X) * vspeed;
        double endx = tableWidth;
        std::cout << "Endy: " << endy << std::endl;
        std::cout << "Endx: " << endx << std::endl;

        X = endx;
        Y = endy;
        updated = true;
        topDone = true;

    }
 
	//run thread
	void BallPositionCalculator::run()
	{
		std::cout << "Start run" << std::endl;
		while (running)
		{
            if (!queueSidePosition.isDefault)
            {
                sideMutex.lock();
                currentSidePosition = queueSidePosition;
                queueSidePosition = VisionPosition();
                sideMutex.unlock();

                calculateSide(lastSidePosition, currentSidePosition);
                lastSidePosition = currentSidePosition;
            }
                
                
             if(!queueTopPosition.isDefault)
			{

                topMutex.lock();
                currentTopPosition = queueTopPosition;
                queueTopPosition = VisionPosition();
                topMutex.unlock();
               
                calculateTop(lastTopPosition, currentTopPosition);
               
                lastTopPosition = currentTopPosition;

			}

             if (sideDone && topDone && updated)
             {
                 std::cout << "Sending: " << X  << "\t" << Y << "\t" << Z << "\t" << theTime << "\t" << std::endl;
                 robotControl->moveArm(Trajectory(Vector(X, Y, Z), theTime));
                 updated = false;

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

  

}