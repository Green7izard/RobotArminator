#pragma once
#include "IRobotControl.hpp"
#include <iostream>
#include "Vector.hpp"
#include <Windows.h>

using namespace Robot;

class RobotControl : public IRobotControl
{
public:
    RobotControl();
    ~RobotControl();
    void moveArm(Vector aPosition);
    Vector getPosition();
    void hitBall(Vector aPosition);
    void setupCommunication(std::string aComport);
    void sendData(std::string aData);
    void receiveData(const int aDataSize);
private:
    
    HANDLE createHandle(std::string aComport);
    void setupHandleParameters();
    void setupHandleTimeouts();
    void closeHandle(HANDLE aHandle);
    
    HANDLE handle;
};


