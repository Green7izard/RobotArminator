#pragma once
#include "Orientation.hpp"
#include "MessageSender.hpp"
#include "VisionPosition.hpp"

namespace ComputerVision
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

