#pragma once
#include "stdafx.h"

#include "VisionPosition.hpp"
#include "Position.hpp"
#include "ABCFormule.hpp"
#include <ctime>


namespace BallPosition
{
	using namespace RobotArminator;

	class BallPositionCalculator
	{
	public:
		float tableWidth = 2740.0;

		VisionPosition lastSidePosition = VisionPosition(1000, 300, Clock::universal_time(), SIDE);
		VisionPosition lastTopPosition = VisionPosition(1000, 300, Clock::universal_time(), TOP);

		VisionPosition currentSidePosition;
		VisionPosition currentTopPosition;

		ABCFormule abcCalculator = ABCFormule();

		BallPositionCalculator();
		virtual ~BallPositionCalculator();

		void run();
		void startPositionCalculation();
		VisionPosition getPositionsFromQueue();
		Position calculateHitPosition(VisionPosition newSideView, VisionPosition newTopView);
		float calculateLiniairPosition(VisionPosition pos);
		void sendPosition();
	};
}