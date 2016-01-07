// DemoArminator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TCPRobot.hpp"
#include "RobotControl.hpp"
#include "Trajectory.hpp"
#include "RobotPositionSetter.cpp"
#include <sstream>

using namespace std;
using namespace Robot;



bool shouldStopException(exception& e) {
    string command;
    cout << "An error occured: " << e.what() << endl;
    cout << "Retry? (y/n)" << endl;
    cin >> command;
    cout << endl;
    if (command.find("n") == string::npos)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Vector toVector(string input)
{
    cout << "Received: " << input << endl;
    std::stringstream ss(input);

    int x, y, z;
    ss >> x;
    ss >> y;
    ss >> z;
    cout << "X=" << x << " Y=" << y << " Z=" << z << endl;
    return Vector(x, y, z);
}

void commandHandler()
{
    string command;
    IRobotControl* controller = nullptr;
    TCPRobot* robot = nullptr;
    do {
        try {
            robot = new TCPRobot();
            controller = new RobotControl(robot);
        }
        catch (std::ios_base::failure& e)
        {
            if (shouldStopException(e))
            {
                return;
            }
        }
        catch (std::ios_base::failure * e)
        {
            if (shouldStopException(*e))
            {
                return;
            }
        }
    } while (controller == nullptr || robot == nullptr);
    controller->start();

    RobotPositionSetter setter;
    cout << "Enter your commands. Typ 'quit' to exit program" << endl;

    for (;;)
    {
       setter.handleCommand(toVector(controller->readData()), *controller);
    }
    
}

int main()
{
    commandHandler();
    return 0;
}

