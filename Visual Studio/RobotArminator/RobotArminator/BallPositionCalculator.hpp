#pragma once
#include "VisionPosition.hpp"
#include <ctime>

namespace BallPosition
{
	using namespace RobotArminator;

	class BallPositionCalculator
	{
	public:
		int tableWidth = 2740;

		VisionPosition lastSidePosition = VisionPosition(1000, 300, std::time_t(5), SIDE);
		VisionPosition lastTopPosition = VisionPosition(1000, 300, std::time_t(5), TOP);

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