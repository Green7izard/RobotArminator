#pragma once
#include "IRobotControl.hpp"
#include "IMessageBox.hpp"
#include "Trajectory.hpp"
namespace ArmMovement
{
    using namespace Robot;

    class IArmMovementCalculator : public IMessageBox<Trajectory>
    {
    public:
        IArmMovementCalculator(IRobotControl * robotControl);
        virtual ~IArmMovementCalculator()=0;
    protected:
        IRobotControl * robotControl;

    };

}