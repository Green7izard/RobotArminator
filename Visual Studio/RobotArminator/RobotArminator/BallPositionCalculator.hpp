#pragma once
#include "VisionPosition.hpp"


class BallPositionCalculator
{
public:
	RobotArminator::VisionPosition currentPosition;

	void run();
	void startPositionCalculation();
	RobotArminator::VisionPosition getPositionsFromQueue();
	void calculateTwoPositionToOnePosition(RobotArminator::VisionPosition pos1, RobotArminator::VisionPosition pos2);
	void sendPosition();

	BallPositionCalculator();
	virtual ~BallPositionCalculator();
};

