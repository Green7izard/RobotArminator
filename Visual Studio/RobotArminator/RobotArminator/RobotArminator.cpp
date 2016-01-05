// RobotArminator.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Controller.hpp"

using namespace RobotArminator;

int main(int argc, char* argv[])
{
    Controller t = Controller(2100, 1400);
    std::string command;
    do
    {
        cin >> command;
    } while (command.compare("quit") != 0);
    //Controller controller;
    return 0;
}
