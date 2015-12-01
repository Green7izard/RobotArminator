#include <iostream>
#include <math.h>
#include "ABCFormule.hpp"

ABCFormule::ABCFormule()
{
}


ABCFormule::~ABCFormule()
{
}

void ABCFormule::setFormule(VisionPosition newSideView, VisionPosition oldSideView, float startValue)
{
	float corner; //degrees
	float height; //meters
	float speed; //meter/seconds
	float distance; //meters
	float PI = 3.14159265358979;
	startPositionX = startValue; // Millimeters

	corner = atan((newSideView.Y - oldSideView.Y) / (newSideView.X - oldSideView.X)) * 180 / PI;
	height = newSideView.Y / 1000;
	/*
	TODO Fix Time comparison

	distance = sqrt(((newSideView.Y - lastSideView.Y) * (newSideView.Y - lastSideView.Y)) + ((newSideView.X - lastSideView.X) * (newSideView.X - lastSideView.X))) / 1000; //meters
	speed = distance / (pos.time - lastSidePosition.time);
	*/
	speed = 5;

	a = (-9.81 / (2 * speed * speed)) * (tan(corner * PI / 180) + 1);
	b = tan(corner * PI / 180);
	c = height;
}

float ABCFormule::getLargestXPosition(float y)
{
	float xPlus = (-b + sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To Millimeters
	float xMin = (-b - sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To Millimeters

	if (xMin >= xPlus) {
		return xMin + startPositionX;
	}
	else {
		return xPlus + startPositionX;
	}
	return NULL; // Return x in millimeters
}

float ABCFormule::getYPosition(float x)
{
	float xInMeters = (x-startPositionX) / 1000;
	float yValue = ((b * xInMeters) + (a * (xInMeters * xInMeters)) + c) * 1000;
	return yValue; // Return y in millimeters
}
