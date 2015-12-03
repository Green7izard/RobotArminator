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
//#include "RobotControl.hpp"

using namespace RobotArminator;

double degToRad(int deg)
{
    return deg * (3.14159265/180);
}
std::string bruteForce(int resultX, int resultY)
{
    for (int j2 = -60; j2 <= 120; j2++)//
    {
        for (int j3 = -110; j3 <= 120; j3++)//
        {
            for (int j5 = -90; j5 <= 90; j5++)//
            {
                int j2y = sin(degToRad(j2)) * 250;
                int j3y = sin(degToRad(j2) + degToRad(j3)) * 160;
                int j5y = sin(degToRad(j2) + degToRad(j3) + degToRad(j5)) * 72;
                int y = j2y + j3y + j5y;
                
                int x = (cos(degToRad(j2)) * 250) + (cos(degToRad(j2) + degToRad(j3)) * 160) + (cos(degToRad(j2) + degToRad(j3) + degToRad(j5)) * 72);
                if (resultX == x && resultY == y)
                {
                    
                    std::cout << j2y << "-" << j3y << "-" << j5y << std::endl;
                    std::stringstream ss;
                    ss << "PRN 1,(90," << j2 << "," << j3 << ",0," << j5 << ",90)\r";
                    std::cout << ss.str() << std::endl;
                    return ss.str();
                }
            }
        }
    }
    return "PRN 1,(90,0,0,0,0,0)\r";
}
int main(int argc, char* argv[])
{ 
    SimpleSerial serial("COM3", 19200);
    Sleep(500);
    //serial.setupRobot();

    serial.writeString("PRN 1,(90,0,0,0,0,0)\r");
    std::cout << serial.readLine() << std::endl;
    Sleep(500);
    //std::cout << sin(degToRad(180)) *250 << "  " << sin(180) *250 << std::endl;

 
    //serial.writeString(bruteForce(40, 20));
    serial.writeString(bruteForce(322, 160));
    std::cout << serial.readLine() << std::endl;
    std::cin.get();
    //serial.run();
    return 0;
}