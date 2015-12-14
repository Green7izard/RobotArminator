#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include "ABCFormule.hpp"

ABCFormule::ABCFormule()
{
}


ABCFormule::~ABCFormule()
{
}

void ABCFormule::setFormule(VisionPosition newSideView, VisionPosition oldSideView, float startValue, bool withSpeed)
{
	float corner; //In degrees
	float height; //In meters
	float speed; //In meter/seconds
	float distance; //In meters
	float PI = 3.14159265358979;
	startPositionX = startValue; //In mMillimeters

	corner = atan((newSideView.Y - oldSideView.Y) / (newSideView.X - oldSideView.X)) * 180 / PI;
	height = newSideView.Y / 1000; //To meters

	distance = sqrt(((newSideView.Y - oldSideView.Y) * (newSideView.Y - oldSideView.Y)) + ((newSideView.X - oldSideView.X) * (newSideView.X - oldSideView.X))) / 1000; //To meters
	if (withSpeed)
	{
		//boost::posix_time::time_duration tempTime (newSideView.time - oldSideView.time);

		std::cout << "difference: " << (float)(newSideView.time - oldSideView.time).total_milliseconds() / 1000 << std::endl;
		std::cout << "distance: " << distance << std::endl;
		speed = distance / (float)((newSideView.time - oldSideView.time).total_milliseconds() / 1000.0); //To meter/seconds
		std::cout << "Speed: " << speed << std::endl;
	}
	else if (lastSpeed != NULL)
	{
		speed = lastSpeed * 0.6;
		/*
		Bij 14 cm hoogte kaatst hij tot 9 cm
		Bij 12 cm hoogte kaatst hij tot 7,5 cm
		*/
	}
	else
	{
		speed = 5;
	}

	a = (-9.81 / (2 * speed * speed)) * (tan(corner * PI / 180) + 1);
	b = tan(corner * PI / 180);
	c = height;
	lastSpeed = speed;
}

float ABCFormule::getLargestXPosition(float y)
{
	float xPlus = (-b + sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To millimeters
	float xMin = (-b - sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To millimeters

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

float ABCFormule::getTime(int startXValue, int endXValue)
{
	int firstY;
	int secondY;

	int fisrtX = startXValue;

	int deltaX;
	int deltaY;

	float distance = 0;

	for (int secondX = startXValue + 10; secondX < endXValue; secondX += 10)
	{
		firstY = getYPosition(fisrtX);
		secondY = getYPosition(secondX);

		deltaX = secondX - fisrtX;
		deltaY = secondY - firstY;

		fisrtX = secondX;
		distance += sqrt(deltaX * deltaX + deltaY * deltaY);
	}
	return ((distance / 1000) / lastSpeed) * 1000; // In milliseconds
}