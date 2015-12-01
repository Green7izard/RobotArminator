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

	ABCFormule();
	virtual ~ABCFormule();

	void setFormule(VisionPosition newSideView, VisionPosition oldSideView, float startValue);
	float getLargestXPosition(float y);
	float getYPosition(float x);
};

