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

void ABCFormule::setFormule(VisionPosition newSideView, VisionPosition oldSideView, double startValue, bool withSpeed)
{
	double corner; //In degrees
	double height; //In meters
	double speed; //In meter/seconds
	double distance; //In meters
	double PI = 3.14159265358979;
	startPositionX = startValue; //In mMillimeters

	corner = atan((newSideView.Y - oldSideView.Y) / (newSideView.X - oldSideView.X)) * 180 / PI;
	height = newSideView.Y / 1000; //To meters

	distance = sqrt(((newSideView.Y - oldSideView.Y) * (newSideView.Y - oldSideView.Y)) + ((newSideView.X - oldSideView.X) * (newSideView.X - oldSideView.X))) / 1000; //To meters
	if (withSpeed)
	{
		//boost::posix_time::time_duration tempTime (newSideView.time - oldSideView.time);

		//std::cout << "difference: " << (float)(newSideView.time - oldSideView.time).total_milliseconds() / 1000 << std::endl;
		//std::cout << "distance: " << distance << std::endl;
		speed = distance / (double)((newSideView.time - oldSideView.time).total_milliseconds() / 1000.0); //To meter/seconds
		//std::cout << "Speed: " << speed << std::endl;
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

	a = (-9.81f / (2 * speed * speed)) * (tan(corner * PI / 180) + 1);
	b = tan(corner * PI / 180);
	c = height;
	lastSpeed = speed;
}

double ABCFormule::getLargestXPositionAtYIsZero()
{
	double xPlus = (-b + sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To millimeters
	double xMin = (-b - sqrt((b*b) - (4 * a * c))) / (2 * a) * 1000; // To millimeters

	if (xMin >= xPlus) {
		return xMin + startPositionX;
	}
	else {
		return xPlus + startPositionX;
	}
	return NULL; // Return x in millimeters
}

double ABCFormule::getYPosition(double x)
{
	double xInMeters = (x-startPositionX) / 1000;
	double yValue = ((b * xInMeters) + (a * (xInMeters * xInMeters)) + c) * 1000;
	return yValue; // Return y in millimeters
}

double ABCFormule::getTime(int startXValue, int endXValue)
{
	int firstY;
	int secondY;

	int fisrtX = startXValue;

	int deltaX;
	int deltaY;

	double distance = 0.0;

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