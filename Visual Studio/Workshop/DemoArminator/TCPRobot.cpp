#include "stdafx.h"
#include "TCPRobot.hpp"

namespace Robot
{
    TCPRobot::TCPRobot(std::string ipAdress, unsigned short port)
    {

        //Start up Winsock…
        WSADATA wsadata;

        int error = WSAStartup(0x0202, &wsadata);

        //Did something happen?
        if (error) {
            throw new std::ios_base::failure("WSA Failed");
        }

        //Socket address information
        SOCKADDR_IN target;
        // address family Internet
        target.sin_family = AF_INET;
        //Port to connect on
        target.sin_port = htons(port);
        //Target IP
        target.sin_addr.s_addr = inet_addr(ipAdress.c_str());

        connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket

        if (connect(connection, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
        {
            //Couldn't connect
            throw new std::ios_base::failure("Could not connect to target");
        }
    }


    TCPRobot::~TCPRobot()
    {
        if (connection)
        {
            closesocket(connection);
        }
        WSACleanup(); //Clean up Winsock
    }

    bool Robot::TCPRobot::sendMessage(std::string message)
    {
        return send(connection, message.c_str(), static_cast<int>(message.length()), 0) > 0;
    }

    std::string TCPRobot::readMessage() {
        char buffer[128];
        recv(connection, buffer, sizeof(buffer), 0);
        return std::string(buffer);
    }
}
