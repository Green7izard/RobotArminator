#pragma once
#include "stdafx.h"
#include "VisionPosition.hpp"

using namespace RobotArminator;

class ABCFormule
{
public:
	double a;
	double b;
	double c;
	double startPositionX;
	double lastSpeed;

	ABCFormule();
	virtual ~ABCFormule();

	void setFormule(VisionPosition newSideView, VisionPosition oldSideView, double startValue, bool withSpeed);
	double getLargestXPositionAtYIsZero();
	double getYPosition(double x);
	double getTime(int startXValue, int endXValue);
};

