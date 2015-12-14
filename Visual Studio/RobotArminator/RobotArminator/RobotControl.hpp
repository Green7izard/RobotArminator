#pragma once

//#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#define _WEBSOCKETPP_NOEXCEPT_
#define WEBSOCKETPP_CPP11_CHRONO

#include "IRobotControl.hpp"
#include <iostream>
#include <functional>
#include "asio.hpp"
#include "Thread.hpp"
#include "Trajectory.hpp"

using namespace Robot;

class RobotControl : public IRobotControl
{
public:
    RobotControl(std::string port, unsigned int baud_rate);
    ~RobotControl();
    void moveArm(Trajectory aTrajectory);
    Trajectory getPosition();
    void hitBall(Trajectory aTrajectory);
    void writeData(std::string aData);
    void writeHandler(const asio::error_code& error) {};
    std::string readData();
    virtual void run() override;
    std::string calculateAngles(Trajectory aTrajectory);
private:
    double getRadian(double aDegree);
    Trajectory adaptTrajectory(Trajectory aTrajectory);
    asio::streambuf buffer;
    asio::io_service io;
    asio::serial_port serial;
};



