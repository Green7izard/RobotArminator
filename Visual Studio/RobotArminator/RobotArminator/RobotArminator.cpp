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
//#include "RobotControl.hpp"

typedef std::chrono::high_resolution_clock Clock;
using namespace RobotArminator;

double degToRad(int deg)
{
    return deg * (3.14159265/180);
}
std::string bruteForce(int resultX, int resultY)
{


    for (int j1 = -90; j1 <= 90; j1 += 180)
    {
        for (int j2 = -60; j2 <= 120; j2+=5)//
        {
            for (int j3 = -110; j3 <= 120; j3+=5)//
            {
                for (int j5 = -90; j5 <= 90; j5+=5)//
                {
                    for (int j6 = -90; j6 <= 90; j6 += 180)
                    {
                        int x;
                        int y;
                        if (j1 < 0)
                        {
                            double j2y = cos(degToRad(j2 * -1)) * 250;
                            double j3y = cos(degToRad(j2 * -1) + degToRad(j3 * -1)) * 160;
                            double j5y = cos(degToRad(j2 * -1) + degToRad(j3 * -1) + degToRad(j5 * -1)) * 72;
                            double j6y = cos(degToRad(j2 * -1) + degToRad(j3 * -1) + degToRad(j5 * -1) + degToRad(j6 * -1)) * 390;
                            y = j2y + j3y + j5y + j6y;

                            double j2x = sin(degToRad(j2 * -1)) * 250;
                            double j3x = sin(degToRad(j2 * -1) + degToRad(j3 * -1)) * 160;
                            double j5x = sin(degToRad(j2 * -1) + degToRad(j3 * -1) + degToRad(j5 * -1)) * 72;
                            double j6x = sin(degToRad(j2 * -1) + degToRad(j3 * -1) + degToRad(j5 * -1) + degToRad(j6 * -1)) * 390;
                            x = j2x + j3x + j5x + j6x;
                        }
                        else
                        {
                            double j2y = cos(degToRad(j2)) * 250;
                            double j3y = cos(degToRad(j2) + degToRad(j3)) * 160;
                            double j5y = cos(degToRad(j2) + degToRad(j3) + degToRad(j5)) * 72;
                            double j6y = cos(degToRad(j2) + degToRad(j3) + degToRad(j5) + degToRad(j6)) * 390;
                            y = j2y + j3y + j5y + j6y;

                            double j2x = sin(degToRad(j2)) * 250;
                            double j3x = sin(degToRad(j2) + degToRad(j3)) * 160;
                            double j5x = sin(degToRad(j2) + degToRad(j3) + degToRad(j5)) * 72;
                            double j6x = sin(degToRad(j2) + degToRad(j3) + degToRad(j5) + degToRad(j6)) * 390;
                            x = j2x + j3x + j5x + j6x;
                        }
                        if (resultX >= x - 50 && resultX <= x + 50  && resultY >= y - 50 && resultY <= y + 50)
                        {
                            std::stringstream ss;
                            if (j1 < 0)
                            {
                                j2 *= -1;
                                j3 *= -1;
                                j5 *= -1;
                                j6 *= -1;
                            }
                            ss << "PRN 1,(" << j1 << "," << j2 << "," << j3 << ",0," << j5 << "," << j6 - 90 << ")\r";
                            std::cout << ss.str() << std::endl;
                            return ss.str();
                        }
                    }
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

    serial.writeString("PRN 1,(-90,0,0,0,0,0)\r");
    std::cout << serial.readLine() << std::endl;
    Sleep(500);
    //std::cout << sin(degToRad(180)) *250 << "  " << sin(180) *250 << std::endl;


    int x = 000;
    int y = 400;
    //serial.writeString(bruteForce(40, 20));
    auto t1 = Clock::now();
    serial.writeString(bruteForce(x, y));
    auto t2 = Clock::now();
    std::cout << "Delta t2-t1: "
        << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
        << " nanoseconds" << std::endl;
    std::cout << serial.readLine() << std::endl;

    char input;
    while (1)
    {

        fflush(stdin);
        input = _getch();
        if (input == 'w')
            x += 5;
        if (input == 's')
            x -= 5;
        if (input == 'a')
            y -= 5;
        if (input == 'd')
            y += 5;
        serial.writeString(bruteForce(x, y));
        std::cout << serial.readLine() << std::endl;
    }
    std::cin.get();
    return 0;
}