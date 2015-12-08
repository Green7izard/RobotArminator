#pragma once
#include "VisionPosition.hpp"

using namespace RobotArminator;

class ABCFormule
{
public:
	float a;
	float b;
	float c;
	float startPositionX;
	float lastSpeed;

	ABCFormule();
	virtual ~ABCFormule();

	void setFormule(VisionPosition newSideView, VisionPosition oldSideView, float startValue, bool withSpeed);
	float getLargestXPosition(float y);
	float getYPosition(float x);
	float getTime(int startXValue, int endXValue);
};

