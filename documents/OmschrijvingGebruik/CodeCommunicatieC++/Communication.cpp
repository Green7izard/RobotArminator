#include "Communication.hpp"



Communication::Communication(std::string port) : io(), serial(io, port)
{
	serial.set_option(boost::asio::serial_port_base::baud_rate(19200));
	serial.set_option(boost::asio::serial_port_base::character_size(8));
	serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
	serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::two));
	serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even));
}


Communication::~Communication()
{
	serial.close();
}

void Communication::writeData(std::string aData)
{
	boost::asio::write(serial, boost::asio::buffer(aData.c_str(), aData.size()));
}

std::string Communication::readData()
{
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