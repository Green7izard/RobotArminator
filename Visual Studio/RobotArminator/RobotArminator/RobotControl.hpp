#pragma once
#include "IRobotControl.hpp"
#include <iostream>
#include <Windows.h>

class RobotControl : public IRobotControl
{
public:
    RobotControl();
    ~RobotControl();
    void moveArm(Position aPosition);
    Position getPosition();
    void hitBall(Position aPosition);
private:
    void sendData(std::string aData);
    std::string receiveData();
    void initCommunication(std::string aComport);
    HANDLE createHandle(std::string aComport);
    void setHandleParameters();
    void setHandleTimeouts();
    HANDLE handle;
};
