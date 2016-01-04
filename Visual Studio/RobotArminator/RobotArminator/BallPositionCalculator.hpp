#pragma once
#include "stdafx.h"

#include "VisionPosition.hpp"
#include "Position.hpp"
#include "ABCFormule.hpp"
#include "Thread.hpp"
#include "IMessageBox.hpp"
#include <mutex>
#include "IBallPositionCalculator.hpp"

namespace BallPosition
{
    using namespace RobotArminator;

    class BallPositionCalculator : public IBallPositionCalculator
    {
    public:
        double tableWidth;

        VisionPosition lastSidePosition;
        VisionPosition lastTopPosition;

        VisionPosition currentSidePosition;
        VisionPosition currentTopPosition;

        VisionPosition queueSidePosition;
        VisionPosition queueTopPosition;

        ABCFormule abcCalculator = ABCFormule();

        BallPositionCalculator(double tableLength);
        virtual ~BallPositionCalculator();

        void run();
        void addToMessageBox(VisionPosition item);

        void getPositionsFromQueue();
        Trajectory calculateHitPosition();
        double calculateLiniairPosition(VisionPosition pos);
        void sendPosition();
    private:
        std::mutex topMutex;
        std::mutex sideMutex;
    };
}