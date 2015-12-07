#pragma once
#include "stdafx.h"

#include "Orientation.hpp"
#include "MessageSender.cpp"
#include "VisionPosition.hpp"

namespace Vision
{
    using namespace RobotArminator;

    class IComputerVision : public MessageSender<VisionPosition>
    {
    public:

      
        virtual ~IComputerVision();

    protected:
        IComputerVision(Orientation orientation);
        Orientation orientation;

    };
}

