#pragma once
#include "stdafx.h"
#include "Orientation.hpp"
#include "MessageSender.hpp"
#include "VisionPosition.hpp"
#include "Thread.hpp"
namespace Vision
{
    using namespace RobotArminator;

    class IComputerVision : public MessageSender, public Thread
    {
    public:    
        virtual ~IComputerVision();
    private:
        Orientation orientation;
    protected:
        IComputerVision(Orientation orientation);

    };
}

