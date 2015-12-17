// RobotArminator.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Controller.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
#include <chrono>
#include "RobotControl.hpp"
#include "BallPositionCalculator.hpp"
#include "Trajectory.hpp"
#include "Vector.hpp"
#include <chrono>
#include <iostream>
using namespace RobotArminator;

int main(int argc, char* argv[])
{ 
    RobotControl robotControl("COM3", 19200);
    Sleep(500);
	BOOST_LOG_TRIVIAL(info) << "Setup complete";
	robotControl.resetPositions();
	Sleep(500);
	//Trajectory beginTrajectory(Vector(0, 762, 350), Clock::universal_time());
	//robotControl.moveArm(beginTrajectory);
    //Sleep(1000);
    Trajectory aTrajectory(Vector(0, 762, 550), Clock::universal_time() + boost::posix_time::seconds(1));
	robotControl.moveArm(aTrajectory);
    //robotControl.writeData(robotControl.calculateAngles(aTrajectory));

	BOOST_LOG_TRIVIAL(info) << "Info";
    std::cin.get(); //wait for user input
    return 0;
}