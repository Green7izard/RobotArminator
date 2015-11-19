#include "IComputerVision.hpp"

namespace Vision {

    using namespace RobotArminator;

    IComputerVision::IComputerVision(Orientation orientation) : MessageSender<VisionPosition>(), orientation(orientation)
    {
    }
    IComputerVision::~IComputerVision()
    {
    }
}