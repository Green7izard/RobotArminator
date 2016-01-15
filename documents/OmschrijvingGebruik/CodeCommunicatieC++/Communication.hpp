#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <functional>

class Communication
{
public:
	Communication(std::string port);
	~Communication();
	void writeData(std::string);
	std::string readData();
private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;
};

