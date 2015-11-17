#pragma once
#include "Orientation.hpp"
#include "MessageSender.hpp"
#include "VisionPosition.hpp"
class IComputerVision : public MessageSender<VisionPosition>
{
public:
   
    IComputerVision(Orientation orientation);
    virtual ~IComputerVision();
private:
    Orientation orientation;

};

