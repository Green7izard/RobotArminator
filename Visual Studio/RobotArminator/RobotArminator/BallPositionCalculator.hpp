#pragma once
#include "VisionPosition.hpp"


class BallPositionCalculator
{
public:
	RobotArminator::VisionPosition lastSidePosition = VisionPosition(0,2,3,UP);
	RobotArminator::VisionPosition lastTopPosition;
	RobotArminator::VisionPosition currentSidePosition;
	RobotArminator::VisionPosition currentTopPosition;

	void run();
	void startPositionCalculation();
	RobotArminator::VisionPosition getPositionsFromQueue();
	void calculateTraject(RobotArminator::VisionPosition pos1, RobotArminator::VisionPosition pos2);
	void calculateLiniairTraject(VisionPosition pos);
	void calculateCircleTraject(VisionPosition pos);
	void sendPosition();

	BallPositionCalculator();
	virtual ~BallPositionCalculator();
};

