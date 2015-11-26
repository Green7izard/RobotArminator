

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

void RobotControl::moveArm(Vector aPosition)
{
}

Vector RobotControl::getPosition()
{
    return Vector();
}

void RobotControl::hitBall(Vector aPosition)
{
}

void RobotControl::setupRobot()
{
    writeData("1;1;OPEN=usertool\r");
    writeData("1;1;CNTLON\r");
    writeData("1;1;RUN1\r");
    writeData("1;2;RUN2\r");
}

void RobotControl::writeData(std::string aData)
{
    asio::write(serial, asio::buffer(aData.c_str(), aData.size()));
}

std::string RobotControl::readData()
{
    //Reading data char by char, code is optimized for simplicity, not speed
    using namespace boost;
    char c;
    std::string result;

    for (;;)
    {
        asio::read(serial, asio::buffer(&c, 1));
        switch (c)
        {
        case '\r':
            break;
        case '\n':
            return result;
        default:
            result += c;
        }
    }
}
