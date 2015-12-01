#pragma once
#include "stdafx.h"

#include "VisionPosition.hpp"


namespace BallPosition
{
	using namespace RobotArminator;

	class BallPositionCalculator
	{
	public:
		int tableWidth = 2740;

		VisionPosition lastSidePosition = VisionPosition(1000, 300, Clock::now(), SIDE);
		VisionPosition lastTopPosition = VisionPosition(1000, 300, Clock::now(), TOP);

		VisionPosition currentSidePosition;
		VisionPosition currentTopPosition;

		void run();
		void startPositionCalculation();
		VisionPosition getPositionsFromQueue();
		void calculateTraject(RobotArminator::VisionPosition pos1, VisionPosition pos2);
		void calculateLiniairTraject(VisionPosition pos);
		void calculateCircleTraject(VisionPosition pos);
		void sendPosition();

		BallPositionCalculator();
		virtual ~BallPositionCalculator();
	};
}