#pragma once
#include "IRobotControl.hpp"
#include "MessageBox.hpp"
#include "Trajectory.hpp"
namespace ArmMovementCalculator
{
    using namespace RobotControl;

    class IArmMovementCalculator : public MessageBox<Trajectory>
    {
    public:
        IArmMovementCalculator(IRobotControl robotControl);
        virtual ~IArmMovementCalculator();
    protected:
        IRobotControl robotControl;

    };

}