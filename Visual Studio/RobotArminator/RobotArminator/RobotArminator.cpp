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
#include <chrono>
#include <iostream>
#include <ctime>
using namespace RobotArminator;

typedef std::chrono::high_resolution_clock Clock;
int main(int argc, char* argv[])
{ 
    RobotControl robotControl("COM3", 19200);
    Sleep(500);

    robotControl.writeData("PRN 1,(0,0,0,0,0,0)\r");
    std::cout << robotControl.readData() << std::endl;
    Sleep(500);
{
    Controller t();

    Vector aPosition(200, 200, 0);
    auto t1 = Clock::now();
    robotControl.writeData(robotControl.calculateAngles(aPosition));
    auto t2 = Clock::now();
    std::cout << "Delta t2-t1: "
        << (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() * 0.000000001)
        << " seconds" << std::endl;
    std::cout << robotControl.readData() << std::endl;
    std::cin.get(); //wait for user input
    return 0;
}