#pragma once
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
		int tableWidth = 2740;

		VisionPosition lastSidePosition = VisionPosition(1750, 300, std::time_t(1000), SIDE);
		VisionPosition lastTopPosition = VisionPosition(1750, 400, std::time_t(1000), TOP);

		VisionPosition currentSidePosition;
		VisionPosition currentTopPosition;

		ABCFormule abcCalculator = ABCFormule();

		void run();
		void startPositionCalculation();
		VisionPosition getPositionsFromQueue();
		Position calculateHitPosition(VisionPosition newSideView, VisionPosition newTopView);
		float calculateLiniairPosition(VisionPosition pos);
		void sendPosition();

		BallPositionCalculator();
		virtual ~BallPositionCalculator();
	};
}