#pragma once
#include "Orientation.hpp"
#include "MessageSender.cpp"
#include "VisionPosition.hpp"

namespace Vision
{
    using namespace RobotArminator;

    class IComputerVision : public MessageSender<VisionPosition>
    {
    public:

        IComputerVision(Orientation orientation);
        virtual ~IComputerVision();
    private:
        Orientation orientation;

    };
}

