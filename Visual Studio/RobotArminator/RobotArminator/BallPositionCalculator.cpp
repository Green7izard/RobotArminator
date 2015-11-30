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
		std::cout << "Start!" << std::endl;
	}

	VisionPosition BallPositionCalculator::getPositionsFromQueue()
	{
		currentTopPosition = VisionPosition();
		return currentTopPosition;
	}

	Position BallPositionCalculator::calculateHitPosition(VisionPosition newSideView, VisionPosition newTopView)
	{
		int zValue = calculateLiniairPosition(newTopView); // Y Coordinate of the top-view when reaching the end of the table.
		formule.setFormule(newSideView, lastSidePosition);
		int yValue = calculateCirclePosition(newSideView); // X Coordinate when hitting the table.

		//std::cout << "Hit the table at: ("<< yValue << ",0," << zValue << ")." << std::endl;
		Position p = Position(Vector(tableWidth, yValue, zValue), 0);
		return p;
	}

	int BallPositionCalculator::calculateLiniairPosition(VisionPosition pos)
	{
		float multiplier = (float)(pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		int startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		int newY = (multiplier * tableWidth) + startValue;
		return newY;
	}

	int BallPositionCalculator::calculateCirclePosition(VisionPosition startPos)
	{
		int hitTablePosition = calculateCircleTraject(startPos);


		//int hitRobotPosition = calculateCircleTraject(startPos);
		return hitTablePosition;
	}

	int BallPositionCalculator::calculateCircleTraject(VisionPosition pos)
	{
		//www.hhofstede.nl/modules/projectielbanen.htm
		
		float corner; //degrees
		float height; //meters
		float speed = 5; //meter/seconds
		float distance; //meters
		float PI = 3.14159265358979;

		corner = atan((pos.Y - lastSidePosition.Y) / (pos.X - lastSidePosition.X)) * 180 / PI;
		std::cout << "Corner: " << corner << std::endl;

		height = pos.Y / 1000;
		std::cout << "Height: " << height << std::endl;

		distance = sqrt(((pos.Y - lastSidePosition.Y) * (pos.Y - lastSidePosition.Y)) + ((pos.X - lastSidePosition.X) * (pos.X - lastSidePosition.X))) / 1000; //meters
		//speed = distance / (pos.time - lastSidePosition.time);
		speed = 5;
		std::cout << "Speed: " << speed << std::endl;
		float a = (-9.81 / (2 * speed * speed)) * (tan(corner * PI / 180) + 1);
		float b = tan(corner * PI / 180);
		float c = height;

		//y = (b * x) + (a * x^2) + c;
		//y = (tan(-22) * x) + (((-9.81 / 25) * (tan(-22) + 1)) *x^2) + 0.2

		float xPlus = (-b + sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // Millimeters
		float xMin = (-b - sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // Millimeters
		std::cout << "PLUS: " << xPlus << std::endl;
		std::cout << "MIN : " << xMin << std::endl;

		if (xMin > xPlus) {
			return xMin + pos.X;
		}
		else {
			return xPlus + pos.X;
		}
		
		return 0;
	}

	void BallPositionCalculator::sendPosition()
	{
	}

}