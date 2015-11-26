

#include "RobotControl.hpp"


RobotControl::RobotControl() : handle(NULL)
{
}

RobotControl::~RobotControl()
{
    if (handle != NULL)
    {
        closeHandle(handle);
    }
}

void RobotControl::moveArm(Vector aPosition)
{
}

Vector RobotControl::getPosition()
{
    return Vector();
}

void RobotControl::hitBall(Vector aPosition)
{
}

void RobotControl::setupCommunication(std::string aComport)
{
    createHandle(aComport);
    setupHandleParameters();
    setupHandleTimeouts();
}

HANDLE RobotControl::createHandle(std::string aComport)
{
    HANDLE hSerial;

    hSerial = CreateFile((LPCSTR)aComport.c_str(),
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
            //TODO: Logger serial port does not exist
        }
        //TODO: Logger some other error occurred.
        return false;
    }
    return hSerial;
}

void RobotControl::setupHandleParameters()
{
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(handle, &dcbSerialParams))
    {
        //TODO: Logger error getting state.
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = TWOSTOPBITS;
    dcbSerialParams.Parity = EVENPARITY;

    if (!SetCommState(handle, &dcbSerialParams))
    {
        //TODO: Logger error setting serial port state.
    }
}

void RobotControl::setupHandleTimeouts()
{
    COMMTIMEOUTS timeouts = { 0 };

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(handle, &timeouts))
    {
        //TODO: Logger error occurred.
    }
}

void RobotControl::closeHandle(HANDLE aHandle)
{
    CloseHandle(aHandle);
}

void RobotControl::sendData(char *aBuffer, int aBufferSize)
{

    std::cout << aBuffer << std::endl;
    DWORD dwBytesSend = 0;
    OutputDebugString(aBuffer);
    if (!WriteFile(handle, (void *)aBuffer, aBufferSize, &dwBytesSend, 0))
    {
        //TODO: Logger
    }
}

void RobotControl::receiveData(const int aDataSize)
{
    char szBuff[10 + 1] = { 0 };
    DWORD dwBytesRead = 0;

    if (!ReadFile(handle, szBuff, 10, &dwBytesRead, NULL))
    {
        //TODO: Logger error occurred.
    }
    std::cout << "Data received: " << szBuff << std::endl;
}
