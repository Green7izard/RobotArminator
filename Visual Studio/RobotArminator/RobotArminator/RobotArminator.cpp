// RobotArminator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "stdafx.h"
#include "Controller.hpp"
#include "SimpleSerial.hpp"
#include <iostream>
#include "conio.h"
#include <sstream>
#include "RobotControl.hpp"

using namespace RobotArminator;

int main(int argc, char* argv[])
{
    SimpleSerial serial("COM3", 19200);
    //serial.setupRobot();
    serial.writeString("1;1;OPEN=usertool\r");
    serial.writeString("1;1;CNTLON\r");
    serial.writeString("1;1;RUN1\r");
    serial.writeString("1;2;RUN2\r");
    serial.writeString("PRN 1,(0,0,0,0,0,0)\r");
    Sleep(2000);
    //serial.writeString("PRN 1,(90,-30,90,0,90,90)\r");
    //Sleep(500);
    //serial.writeString("PRN 1,(0,0,0,0,0,0)\r");
    char input;
    int j1 = 0;
    int j2 = 0;
    int j3 = 0;
    int j5 = 0;
    int j6 = 0;
    while (1)
    {
        input = _getch();

        if (input == 'q' && j1 <= 145)
            j1 += 5;
        if (input == 'a' && j1 >= -145)
            j1 -= 5;

        if (input == 'w' && j2 <= 115)
            j2 += 5;
        if (input == 's' && j2 >= -55)
            j2 -= 5;

        if (input == 'e' && j3 <= 115)
            j3 += 5;
        if (input == 'd' && j3 >= -105)
            j3 -= 5;

        if (input == 'r' && j5 <= 85)
            j5 += 5;
        if (input == 'f' && j5 >= -85)
            j5 -= 5;

        if (input == 't' && j6 <= 195)
            j6 += 5;
        if (input == 'g' && j6 >= -195)
            j6 -= 5;

        if (input == 'z' && j6 <= 195)
            j6 += 50;
        if (input == 'x' && j6 >= -195)
            j6 -= 50;

        if (input == 'p')
        {
            j1 = 0;
            j2 = 0;
            j3 = 0;
            j5 = 0;
            j6 = 0;
        }
        std::stringstream ss;
        ss << "PRN 1,(" << j1 << "," << j2 << "," << j3 << ",0," << j5 << "," << j6 << ")\r";
        serial.writeString(ss.str());
        Sleep(200);
    }
   
    return 0;
}