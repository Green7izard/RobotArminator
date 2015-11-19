#pragma once
#include "IRobotControl.hpp"
#include "MessageBox.hpp"
#include "Trajectory.hpp"
namespace ArmMovement
{
    using namespace Robot;

    class IArmMovementCalculator : public MessageBox<Trajectory>
    {
    public:
        IArmMovementCalculator(IRobotControl robotControl);
        virtual ~IArmMovementCalculator();
    protected:
        IRobotControl robotControl;

    };

}