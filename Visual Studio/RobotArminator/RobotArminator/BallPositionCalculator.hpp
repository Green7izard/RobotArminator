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


        double TimeBeforeTableEnd(double startX, double speedX, double startTime);
        double CalculateXSpeed(VisionPosition p1, VisionPosition p2);
        double CalculateYSpeed(VisionPosition p1, VisionPosition p2);
        double CalculateXFromTime(double start, double speed, double time);
        double CalculateTimeWhenZero(double StartHeight, double upwardSpeedInMS);
        double CalculateYSpeed(double currentSpeed, double time);
        double CalculateHeightForT(double timeInS, double StartHeight, double upwardSpeedInMS);
        void calculateSide(VisionPosition p1, VisionPosition p2);
        void calculateTop(VisionPosition p1, VisionPosition p2);

    private:
        std::mutex topMutex;
        std::mutex sideMutex;
    };
}