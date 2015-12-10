

#include "RobotControl.hpp"

RobotControl::RobotControl(std::string port, unsigned int baud_rate)
    : io(), serial(io, port)
{
    serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
    serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::two));
    serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
}

RobotControl::~RobotControl()
{
    serial.close();
}

void RobotControl::moveArm(Trajectory aTrajectory)
{
}

Trajectory RobotControl::getPosition()
{
    return Trajectory();
}


void RobotControl::hitBall(Trajectory aTrajectory)
{
}

void RobotControl::writeData(std::string aData)
{
    asio::async_write(serial, asio::buffer(aData.c_str(), aData.size()), std::bind(&RobotControl::writeHandler,
        this, std::placeholders::_1));
}

void RobotControl::writeHandler(
    const asio::error_code& error)
{
    if (!error)
    {
        std::stringstream ss;
        ss << &buffer;
        std::cout << "Message: " << ss.str() << std::endl;
    }
    else
    {
        std::cout << "Error occurred." << std::endl;
    }
}

std::string RobotControl::readData()
{
    /*
    asio::async_read_until(serial, buffer, '\r', std::bind(&RobotControl::writeHandler,
        this, std::placeholders::_1));;
    std::ostringstream ss;
    ss << &buffer;

    std::cout << "Message: " << ss.str() << std::endl;
    return ss.str();
    */
    
    
    //Reading data char by char, code is optimized for simplicity, not speed
    char c;
    std::string result;
    for (;;)
    {
        asio::read(serial, asio::buffer(&c, 1));
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
    for (int j1 = -90; j1 <= 90; j1 += 180)
    {
        for (int j2 = -60; j2 <= 120; j2 += 5)
        {
            for (int j3 = -110; j3 <= 120; j3 += 5)
            {
                for (int j5 = -90; j5 <= 90; j5 += 5)
                {
                    for (int j6 = -90; j6 <= 90; j6 += 180)
                    {
                        int x;
                        int y;
                        double j2y = cos(getRadian(j2)) * 250;
                        double j3y = cos(getRadian(j2) + getRadian(j3)) * 160;
                        double j5y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        double j6y = cos(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        y = j2y + j3y + j5y + j6y;

                        double j2x = sin(getRadian(j2)) * 250;
                        double j3x = sin(getRadian(j2) + getRadian(j3)) * 160;
                        double j5x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5)) * 72;
                        double j6x = sin(getRadian(j2) + getRadian(j3) + getRadian(j5) + getRadian(j6)) * 390;
                        x = j2x + j3x + j5x + j6x;

                        if (aTrajectory.position.x >= x - 50 && aTrajectory.position.x <= x + 50 && aTrajectory.position.y == y/* - 50 && aTrajectory.position.y <= y + 50*/)
                        {
                            std::stringstream ss;
                            ss << "PRN 1,(" << j1 << "," << j2 << "," << j3 << ",0," << j5 << "," << j6 - 90 << ")\r";
                            std::cout << ss.str() << std::endl;
                            return ss.str();
                        }
                    }
                }
            }
        }
    }
    std::cout << "Not found." << std::endl;
    return "PRN 1,(0,0,0,0,0,0)\r";
}

double RobotControl::getRadian(double aDegree)
{
    return aDegree * (3.14159265 / 180);
}