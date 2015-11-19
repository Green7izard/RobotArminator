#pragma once
#include "VisionPosition.hpp"
#include <ctime>

namespace BallPositionCalculator
{
	using namespace RobotArminator;

	class BallPositionCalculator
	{
	public:
		VisionPosition lastSidePosition = VisionPosition(1000, 300, std::time_t(5), SIDE);
		VisionPosition lastTopPosition = VisionPosition(1000, 300, std::time_t(5), TOP);

		VisionPosition currentSidePosition = VisionPosition(2000, 200, std::time_t (4.9), SIDE);
		VisionPosition currentTopPosition = VisionPosition(2000, 500, std::time_t (4.9), TOP);

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