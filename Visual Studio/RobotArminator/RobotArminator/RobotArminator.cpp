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
    RobotControl myControl;
    myControl.setupCommunication("COM3");

    std::cout << "Usertool" << std::endl;
    myControl.sendData("1;1;OPEN=usertool\r", 17);
    Sleep(2000);

    std::cout << "CNTLON" << std::endl;
    myControl.sendData("1;1;CNTLON\r", 10);
    Sleep(2000);

    std::cout << "SRVON" << std::endl;
    myControl.sendData("1;1;SRVON\r", 9);
    Sleep(2000);

    std::cout << "STATE" << std::endl;
    myControl.sendData("1;1;STATE\r", 9);
    Sleep(2000);

    std::cout << "PRN" << std::endl;
    myControl.sendData("PRN (50,50,0,0,0,0)\r", 19);
    //myControl.receiveData(100);
    std::cin.get();
    return 0;
}

