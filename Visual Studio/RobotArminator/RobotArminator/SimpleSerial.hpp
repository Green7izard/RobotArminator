#define ASIO_STANDALONE 
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS

#define _WEBSOCKETPP_NOEXCEPT_
#define WEBSOCKETPP_CPP11_CHRONO

#include <asio.hpp>
#include "conio.h"

class SimpleSerial
{
public:
    /**
    * Constructor.
    * \param port device name, example "/dev/ttyUSB0" or "COM4"
    * \param baud_rate communication speed, example 9600 or 115200
    * \throws boost::system::system_error if cannot open the
    * serial device
    */
    SimpleSerial(std::string port, unsigned int baud_rate)
        : io(), serial(io, port)
    {
        serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
        serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::two));
        serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
    }

    ~SimpleSerial()
    {
        serial.close();
    }

    /**
    * Write a string to the serial device.
    * \param s string to write
    * \throws boost::system::system_error on failure
    */
    void writeString(std::string s)
    {
        asio::write(serial, asio::buffer(s.c_str(), s.size()));
    }

    /**
    * Blocks until a line is received from the serial device.
    * Eventual '\n' or '\r\n' characters at the end of the string are removed.
    * \return a string containing the received line
    * \throws boost::system::system_error on failure
    */
    std::string readLine()
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
                return result;
            default:
                result += c;
            }
        }
    }

    void run()
    {
        while (1)
        {
            char input;
            int j1 = 0;
            int j2 = 0;
            int j3 = 0;
            int j5 = 0;
            int j6 = 0;
            while (1)
            {
                fflush(stdin);
                input = _getch();
                
                if (input == 'q' && j1 <= 145)
                    j1 += 5;
                if (input == 'a' && j1 >= -145)
                    j1 -= 5;

                if (input == 'w' && j2 <= 115)
                    j2 += 5;
                if (input == 's' && j2 >= -55)
                    j2 -= 5;

                if (input == 'e' && j3 <= 115)
                    j3 += 5;
                if (input == 'd' && j3 >= -105)
                    j3 -= 5;

                if (input == 'r' && j5 <= 85)
                    j5 += 5;
                if (input == 'f' && j5 >= -85)
                    j5 -= 5;

                if (input == 't' && j6 <= 195)
                    j6 += 5;
                if (input == 'g' && j6 >= -195)
                    j6 -= 5;

                if (input == 'z' && j6 <= 150)
                    j6 += 50;
                if (input == 'x' && j6 >= -150)
                    j6 -= 50;
                
                if (input == 'p')
                {
                    j1 = 0;
                    j2 = 0;
                    j3 = 0;
                    j5 = 0;
                    j6 = 0;
                }
                std::stringstream ss;
                ss << "PRN 1,(" << j1 << "," << j2 << "," << j3 << ",0," << j5 << "," << j6 << ")\r";
                writeString(ss.str());
                std::cout << readLine() << std::endl;
                Sleep(200);
            }
        }
    }

private:
    asio::io_service io;
    asio::serial_port serial;
};