#pragma once

#include "IRobotControl.hpp"
#include "TCPRobot.hpp"

#include <functional>
#include <iostream>
#include "Trajectory.hpp"
#include "stdafx.h"


using namespace Robot;

class RobotControl : public IRobotControl
{
public:
    RobotControl(TCPRobot * robot);
    ~RobotControl();
    void moveArm(Trajectory aTrajectory);
    virtual void resetPositions() override;
    virtual void run();
private:

    TCPRobot * robot;

    void writeData(std::string aData);
    std::string readData();
    //void writeHandler(const boost::system::error_code& error) {};
    std::string calculateAngles(Trajectory aTrajectory);
    double getRadian(double aDegree);
    Trajectory getTrajectory();
    void setTrajectory(Trajectory aTrajectory);
    Trajectory adaptTrajectory(Trajectory aTrajectory);
    int globalj1;
    Trajectory trajectory;
    bool hasTrajectory;
};



