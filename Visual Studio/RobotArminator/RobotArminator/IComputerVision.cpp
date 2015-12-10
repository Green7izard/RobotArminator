#include "stdafx.h"
#include "IComputerVision.hpp"

namespace Vision {

    using namespace RobotArminator;

    IComputerVision::IComputerVision(Orientation orientation) : MessageSender(), orientation(orientation)
    {
    }
    IComputerVision::~IComputerVision()
    {
    }
}