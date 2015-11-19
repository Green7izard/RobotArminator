#pragma once
#include "MessageSender.hpp"
#include "MessageBox.hpp"
#include "VisionPosition.hpp"
#include "Trajectory.hpp"

namespace BallPosition
{
    using namespace RobotArminator;

    class IBallPositionCalculator : public MessageSender<VisionPosition>, public MessageBox <Trajectory>
    {
    public:
        IBallPositionCalculator();
        ~IBallPositionCalculator();
    };

}