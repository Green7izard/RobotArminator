// DemoArminator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TCPRobot.hpp"
#include "RobotControl.hpp"
#include "Trajectory.hpp"

using namespace std;
using namespace Robot;

//TODO THIS FUNCTION
void handleCommand(string command, IRobotControl &robotControl, TCPRobot &robot)
{

    //The content of this function can be changed to stay in here, endless loop, or run predefined programs!
    //TEST SETTING THE ARM WITH A COMMAND!


    cout << "Received: " << command<<endl;

    //Set all the angles!
    //NOTE, there is no 5th point
    robot.sendMessage("PRN 1,(-150, -90, 58 ,-13, 0, 7)\r");
    cout << "Send 1" << endl;
    Sleep(2000);

    //Only set the values that are not 0
    robot.sendMessage("PRN 2,(150, 90, 0 ,0, 0, 0)\r");
    cout << "Send 2" << endl;
    Sleep(4000);   

    //Reset the position on the controller
    robotControl.resetPositions();
    cout << "Send 3" << endl;
    Sleep(2000);

    //Set the position using a Trajectory
    Vector v(200, 1525, 200);
    Trajectory t(v);
    robotControl.moveArm(t);
    cout << "Send 4" << endl;
}

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

int main()
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
                return -1;
            }
        }
        catch (std::ios_base::failure * e)
        {
            if (shouldStopException(*e))
            {
                return -1;
            }
        }
    } while (controller == nullptr || robot == nullptr);
    controller->start();
    cout << "Enter your commands. Typ 'quit' to exit program" << endl;

    for (;;)
    {
        cin >> command;
        if (command.compare("quit") == 0)
        {
            break;
        }
        else
        {
            handleCommand(command, *controller, *robot);
        }
    }
    return 0;

}

