// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "Controller.hpp"
#include "RobotControl.hpp"
#include <stdlib.h>
#include "SimpleSerial.hpp"

using namespace RobotArminator;

int main(int argc, char* argv[])
{
    Controller controller;
    SimpleSerial serial("COM3", 9600);
    serial.writeString("PRN (0,90,0,0,0,0)");
    //std::cin.get();
    return 0;
}

