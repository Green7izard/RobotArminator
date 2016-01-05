// DemoArminator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TCPRobot.hpp"

using namespace std;
using namespace Robot;

int main()
{
    Robot::TCPRobot robot;
    cout << "Enter your commands. Typ 'quit' to exit program"<<endl;
    string command;
    do {
        cin >> command;
        robot.sendMessage(command);
    } while (command.compare("quit") != 0);
    return 0;
}

