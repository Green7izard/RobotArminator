#include <iostream>
#include <math.h>
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
		calculateCircleTraject(sideView);
	}

	void BallPositionCalculator::calculateLiniairTraject(VisionPosition pos)
	{
		float multiplier = (float)(pos.Y - lastTopPosition.Y) / (pos.X - lastTopPosition.X);
		int startValue = lastTopPosition.Y - (lastTopPosition.X * multiplier);
		int newY = (multiplier * tableWidth) + startValue;
		std::cout << multiplier << " * " << tableWidth << " + " << startValue << " = " << newY << std::endl;

	}

	void BallPositionCalculator::calculateCircleTraject(VisionPosition pos)
	{
		//http://www.hhofstede.nl/modules/projectielbanen.htm
		
		float corner = 20; //degrese
		float height = 0.2; //meters
		float speed = 5; //meter/seconds

		float PI = 3.14159265358979;
		float a = (-9.81 / (2 * speed * speed)) * (tan(corner * PI / 180) + 1);
		float b = tan(corner * PI / 180);
		float c = height;

		//y = (b * x) + (a * x^2) + c;
		float xPlus = (-b + sqrt((b*b) - (4 * a * c))) / (2 * a);
		float xMin = (-b - sqrt((b*b) - (4 * a * c))) / (2 * a);

		std::cout << xPlus;
		std::cout << xMin;
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