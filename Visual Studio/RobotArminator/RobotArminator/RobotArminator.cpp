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
#include <ctime>
using namespace RobotArminator;

int main(int argc, char* argv[])
{ 
    RobotControl robotControl("COM3", 19200);
    Sleep(500);

    robotControl.writeData("PRN 1,(0,0,0,0,0,0)\r");
    std::cout << robotControl.readData() << std::endl;
    Sleep(500);

    Controller t();
    Trajectory aTrajectory(Vector(200, 400, 0), Vector(), 0);
    auto t1 = Clock::now();
    robotControl.writeData(robotControl.calculateAngles(aTrajectory));
    auto t2 = Clock::now();
    std::cout << "Delta t2-t1: "
        << (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 0.000000001)
        << " seconds" << std::endl;
    std::cout << robotControl.readData() << std::endl;
    std::cin.get(); //wait for user input
    return 0;
}