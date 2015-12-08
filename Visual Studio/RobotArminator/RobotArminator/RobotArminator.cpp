// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "Controller.hpp"
#include "SimpleSerial.hpp"
#include <iostream>
#include <math.h>
#include <sstream>
#include <chrono>
#include "RobotControl.hpp"

typedef std::chrono::high_resolution_clock Clock;
using namespace RobotArminator;

int main(int argc, char* argv[])
{ 
    RobotControl robotControl("COM3", 19200);
    Sleep(500);

    robotControl.writeData("PRN 1,(0,0,0,0,0,0)\r");
    std::cout << robotControl.readData() << std::endl;
    Sleep(500);

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