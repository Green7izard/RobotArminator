#pragma once
#include "MessageSender.hpp"
#include "MessageBox.hpp"
#include "VisionPosition.hpp"
#include "Trajectory.hpp"

namespace BallPosition
{
    using namespace RobotArminator;

    class IBallPositionCalculator : public MessageSender<VisionPosition>, public IMessageBox <Trajectory>
    {
    public:
        
        virtual ~IBallPositionCalculator()=0;
    protected:
        IBallPositionCalculator();
    };

}