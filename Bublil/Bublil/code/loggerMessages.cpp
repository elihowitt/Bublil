#include "logger.h"

void lg::sayHello()
{
	std::cout << "Hello world!\n";
}

void lg::log(const std::string& message)
{
	lg::textCol(TEXT_COLOUR::TC_WHITE);
	std::cout << message<<'\n';
}

void lg::err(const std::string & message)
{
	lg::textCol(TEXT_COLOUR::TC_RED);
	std::cout << message << '\n';
}

void lg::warn(const std::string & message)
{
	lg::textCol(TEXT_COLOUR::TC_RED);
	std::cout << message << '\n';
}
