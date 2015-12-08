#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#define _WEBSOCKETPP_NOEXCEPT_
#define WEBSOCKETPP_CPP11_CHRONO

#pragma once
#include "IRobotControl.hpp"
#include <iostream>
#include "Vector.hpp"
#include "asio.hpp"
#include "Windows.h"

using namespace Robot;

class RobotControl : public IRobotControl
{
public:
    RobotControl(std::string port, unsigned int baud_rate);
    ~RobotControl();
    void moveArm(Vector aPosition);
    Vector getPosition();
    void hitBall(Vector aPosition);
    void writeData(std::string aData);
    std::string readData();
    std::string calculateAngles(Vector aPosition);
private:
    double getRadian(double aDegree);
    asio::io_service io;
    asio::serial_port serial;
};


