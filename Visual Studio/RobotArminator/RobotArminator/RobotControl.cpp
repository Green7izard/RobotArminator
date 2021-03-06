#include "stdafx.h"
#include "RobotControl.hpp"
#include <limits> 

/*** Public functions ***/
RobotControl::RobotControl(std::string port, unsigned int baud_rate)
    : io(), serial(io, port)
{
	try {
		serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
		serial.set_option(boost::asio::serial_port_base::character_size(8));
		serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
		serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::two));
		serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even));
		Sleep(500);
		resetPositions();
		Sleep(500);
		start();
		BOOST_LOG_TRIVIAL(info) << "RobotControl setup complete";
	}
	catch (int e){
		BOOST_LOG_TRIVIAL(error) << "Unable to setup robotcontrol: " << e;
	}
}

RobotControl::~RobotControl()
{
    stop();
    serial.close();
}

void RobotControl::moveArm(Trajectory aTrajectory)
{
	setTrajectory(aTrajectory);
}

void RobotControl::resetPositions()
{
	writeData("PRN 1,(0,0,0,0,0,0)\r");
}

void RobotControl::run()
{
	while (isRunning())
	{
		if (hasTrajectory == true)
		{
            Time startTime = Clock::universal_time();       
         	writeData(calculateAngles(getTrajectory()));
			BOOST_LOG_TRIVIAL(info) << readData();
            std::cout << "Tijd tot de response: " << (Clock::universal_time() - startTime).total_milliseconds() << "ms" << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;


			//hitBall(getTrajectory());
			hasTrajectory = false;
		}
	}
}

/*** Private functions ***/
void RobotControl::hitBall(Trajectory aTrajectory)
{
	Sleep(adaptTime(getTrajectory()));
	if (globalj1 == -90)
	{
		writeData("PRN 2,(0,0,0,0,0,30)\r");
	}
	else if (globalj1 == 90)
	{
		writeData("PRN 2,(0,0,0,0,0,-30)\r");
	}
	BOOST_LOG_TRIVIAL(info) << readData();
}

void RobotControl::writeData(std::string aData)
{
	boost::asio::async_write(serial, boost::asio::buffer(aData.c_str(), aData.size()), std::bind(&RobotControl::writeHandler,
		this, std::placeholders::_1));
}

std::string RobotControl::readData()
{
	//Reading data char by char, code is optimized for simplicity, not speed
	char c;
	std::string result;
	for (;;)
	{
		boost::asio::read(serial, boost::asio::buffer(&c, 1));
		switch (c)
		{
		case '\r':
			return result;
		default:
			result += c;
		}
	}
}

std::string RobotControl::calculateAngles(Trajectory aTrajectory)
{
    Time startTime = Clock::universal_time();

    Trajectory trajectory = adaptTrajectory(aTrajectory);
   
    int weight = std::numeric_limits<int>::max();

    int bestJ1 = lastJ1;
    int bestJ2 = lastJ2;
    int bestJ3 = lastJ3;
    int bestJ5 = lastJ5;
    int bestJ6 = lastJ6;

    for (int j1 = -90; j1 <= 90; j1 += 180)
    {
        for (int j2 = -60; j2 <= 120; j2 += 10)
        {
            for (int j3 = -110; j3 <= 120; j3 += 10)
            {
                for (int j5 = -90; j5 <= 90; j5 += 10)
                {
                    for (int j6 = -90; j6 <= 90; j6 += 180)
                    {
                        double j2y = cos(getRadian(j2)) * 250;
                        double j3y = cos(getRadian(j2) + getRadian(j3)) * 160;
                        double j5y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        double j6y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        int y = (int) (j2y + j3y + j5y + j6y);

                        double j2x = sin(getRadian(j2)) * 250;
                        double j3x = sin(getRadian(j2) + getRadian(j3)) * 160;
                        double j5x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        double j6x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        int x = (int) (j2x + j3x + j5x + j6x);

                        if (trajectory.position.x >= x - 50 && trajectory.position.x <= x + 50 && trajectory.position.y >= y - 50 && trajectory.position.y <= y + 50)
                        {
							if ((j1 == 90 && x <= 10 && (j2 + j3 + j5 <= 90)) || (j1 == -90 && x >= -10 && (j2 + j3 + j5 >= -90)))
							{
                                if (trajectory.position.x > 0)
                                    j1 *= -1;
								globalj1 = j1;
								
                                j6 = j6 - 90;

                                int solWeight = std::abs(lastJ1 - j1) + std::abs(lastJ2 - j2) + std::abs(lastJ3 - j3) + std::abs(lastJ5 - j5) + std::abs(lastJ6 - j6);

                           //     std::cout << "Weight is: " << weight << " , " << solWeight << std::endl;
                                
                            //    std::cout << "cor is: " << j1 << " , " << j2 << " , " << j3 << " , " << j5 << " , " << j6 << std::endl;

                                if (solWeight < weight)
                                {
                                  //  std::cout << "Setting new pos: " << std::endl;
                                    weight = solWeight;
                                    bestJ1 = j1;
                                    bestJ2 = j2;
                                    bestJ3 = j3;
                                    bestJ5 = j5;
                                    bestJ6 = j6;
                                }

							    //   std::cout << "Calculating angles took: " << (Clock::universal_time() - startTime).total_milliseconds() << "ms" << std::endl;
								
							}
                        }
                    }
                }
            }
        }
    }
	//BOOST_LOG_TRIVIAL(info) << "No possible position found.";
  
    std::stringstream ss;

    ss << "PRN 1,(" << bestJ1 << "," << bestJ2 << "," << bestJ3 << ",0," << bestJ5 << "," << bestJ6 << ")\r";
   // std::cout << ss.str() << std::endl;
  //  std::cout << "Calculating angles took: " << (Clock::universal_time() - startTime).total_milliseconds() << "ms" << std::endl;

    return ss.str();
}

double RobotControl::getRadian(double aDegree)
{
    return aDegree * (3.14159265 / 180);
}

Trajectory RobotControl::getTrajectory()
{
	return trajectory;
}

void RobotControl::setTrajectory(Trajectory aTrajectory)
{
	trajectory = aTrajectory;
	hasTrajectory = true;
}

Trajectory RobotControl::adaptTrajectory(Trajectory aTrajectory)
{
    return Trajectory(Vector(aTrajectory.position.y - (1400 / 2), aTrajectory.position.z - 350, 0), aTrajectory.time);
}

int RobotControl::adaptTime(Trajectory aTrajectory)
{
	if (Clock::universal_time() <= aTrajectory.time)
	{
        int ret = (int)(aTrajectory.time - Clock::universal_time()).total_milliseconds();
        std::cout << "Waiting: " << ret << std::endl;
		return ret;
	}
    return 0;
}