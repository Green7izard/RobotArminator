#include "stdafx.h"
#include "RobotControl.hpp"


RobotControl::RobotControl()
{

}


RobotControl::~RobotControl()
{
    CloseHandle(handle);
}

void RobotControl::moveArm(Position aPosition)
{
}

Position RobotControl::getPosition()
{
    return Position();
}

void RobotControl::hitBall(Position aPosition)
{
}

void RobotControl::sendCommand(std::string aCommand)
{
    char buffer = aCommand.size();
}

/* setup communication with robotarm via com port. */
void RobotControl::initCommunication(std::string aComport)
{
    createHandle(aComport);
    setHandleParameters();
    setHandleTimeouts();
}

HANDLE RobotControl::createHandle(std::string aComport)
{
    HANDLE hSerial;
    hSerial = CreateFile((LPCWSTR)aComport.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);

    if (hSerial == INVALID_HANDLE_VALUE) 
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            //serial port does not exist, inform user
            //TODO: Logger
        }
        //TODO: Logger, other error
    }
    else
    {
        return hSerial;
    }
}

void RobotControl::setHandleParameters()
{
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(handle, &dcbSerialParams))
    {
        //TODO: Logger: error getting state
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(handle, &dcbSerialParams))
    {
        //TODO: Logger: error setting serial port state
    }
}

void RobotControl::setHandleTimeouts()
{
    COMMTIMEOUTS timeouts = { 0 };

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 50;

    if (!SetCommTimeouts(handle, &timeouts))
    {
        //TODO: Logger: error occured.
    }
}