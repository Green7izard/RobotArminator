#include "stdafx.h"
#include "IRobotControl.hpp"

namespace RobotControl
{
    using namespace RobotArminator;

    IRobotControl::IRobotControl()
    {
    }



    IRobotControl::~IRobotControl()
    {
    }

    void IRobotControl::moveArm(Vector position)
    {
    }

    Vector IRobotControl::getPosition()
    {
        return Vector();
    }

    void IRobotControl::hitBall(Vector position)
    {
    }
}