#include "stdafx.h"
#include "RobotControl.hpp"

/*** Public functions ***/
RobotControl::RobotControl(TCPRobot * robot) : robot(robot), hasTrajectory(false)
{

}

RobotControl::~RobotControl()
{
}

void RobotControl::moveArm(Trajectory aTrajectory)
{
    setTrajectory(aTrajectory);
}

void RobotControl::resetPositions()
{
    writeData("PRN 1,(0,0,0,0,0,0)\r");
}

void RobotControl::run()
{
    while (isRunning())
    {
        if (hasTrajectory == true)
        {
            writeData(calculateAngles(getTrajectory()));
            hasTrajectory = false;
        }
    }
}


void RobotControl::writeData(std::string aData)
{
    robot->sendMessage(aData);
}

std::string RobotControl::readData()
{
    return robot->readMessage();
}

std::string RobotControl::calculateAngles(Trajectory trajectory)
{

    for (int j1 = -90; j1 <= 90; j1 += 180)
    {
        for (int j2 = -60; j2 <= 120; j2 += 1)
        {
            for (int j3 = -110; j3 <= 120; j3 += 1)
            {
                for (int j5 = -90; j5 <= 90; j5 += 1)
                {
                    //for (int j6 = -90; j6 <= 90; j6 += 180)
                    //{
                        double j2y = cos(getRadian(j2)) * 250;
                        double j3y = cos(getRadian(j2) + getRadian(j3)) * 160;
                        double j5y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        //double j6y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        int y = (int)(j2y + j3y + j5y);

                        double j2x = sin(getRadian(j2)) * 250;
                        double j3x = sin(getRadian(j2) + getRadian(j3)) * 160;
                        double j5x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        //double j6x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        int x = (int)(j2x + j3x + j5x);

                        if (trajectory.position.x >= x - 10 && trajectory.position.x <= x + 10 && trajectory.position.y >= y - 10 && trajectory.position.y <= y + 10)
                        {
                            if ((j1 == 90 && x <= 10 && (j2 + j3 + j5 <= 90)) || (j1 == -90 && x >= -10 && (j2 + j3 + j5 >= -90)))
                            {
                                globalj1 = j1;

                                std::stringstream ss;
                                ss << "PRN 1,(" << j1 << "," << j2 << "," << j3 << ",0," << j5 << "," << 0 << ")\r";
                                std::cout << ss.str() << std::endl;

                                return ss.str();
                            }
                        }
                    //}
                }
            }
        }
    }
    return "PRN 1,(0,0,0,0,0,0)\r";
}

double RobotControl::getRadian(double aDegree)
{
    return aDegree * (3.14159265 / 180);
}

Trajectory RobotControl::getTrajectory()
{
    return trajectory;
}

void RobotControl::setTrajectory(Trajectory aTrajectory)
{
    trajectory = aTrajectory;
    hasTrajectory = true;
}

