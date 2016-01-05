#pragma once 
#pragma comment(lib, "Ws2_32.lib")

#include "stdafx.h"
#include <winsock.h>

namespace Robot
{
    class TCPRobot
    {
    private:
        SOCKET connection;
    public:
        //Construct
        TCPRobot(std::string ipAdress = "127.0.0.1", unsigned short port = 63258);
        //Close the connection
        virtual ~TCPRobot();

        //Send a message
        bool sendMessage(std::string message);
        //Try to read a message
        std::string readMessage();
    };
}

