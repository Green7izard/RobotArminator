#include "Communication.hpp"

int main()
{
	Communication communication("COM4");
	communication.writeData("PRN 1,(90,0,0,0,0,0)\r");
	std::cout << communication.readData() << std::endl;
	std::cin.get();
	return 0;
}