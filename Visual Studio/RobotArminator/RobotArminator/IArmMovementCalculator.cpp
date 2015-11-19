#include "stdafx.h"
#include "IArmMovementCalculator.hpp"
namespace ArmMovement
{
    IArmMovementCalculator::IArmMovementCalculator(IRobotControl * robotControl) : robotControl(robotControl)
    {
    }
}