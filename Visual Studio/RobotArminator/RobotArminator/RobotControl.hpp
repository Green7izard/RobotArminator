#pragma once

#include "IRobotControl.hpp"

#include <functional>
#include <iostream>

#include "boost/asio.hpp"
#include "Thread.hpp"
#include "Trajectory.hpp"
#include "stdafx.h"


using namespace Robot;

class RobotControl : public IRobotControl
{
public:
	RobotControl(std::string port, unsigned int baud_rate);
	~RobotControl();
	void moveArm(Trajectory aTrajectory);
	void resetPositions();
	virtual void run() override;
private:
	void hitBall(Trajectory aTrajectory);
	void writeData(std::string aData);
	std::string readData();
	void writeHandler(const boost::system::error_code& error) {};
	std::string calculateAngles(Trajectory aTrajectory);
    double getRadian(double aDegree);
	Trajectory getTrajectory();
	void setTrajectory(Trajectory aTrajectory);
    Trajectory adaptTrajectory(Trajectory aTrajectory);
    int adaptTime(Trajectory aTrajectory);
	int globalj1;
	boost::asio::streambuf buffer;
	boost::asio::io_service io;
	boost::asio::serial_port serial;
	Trajectory trajectory;
	bool hasTrajectory = false;
};



