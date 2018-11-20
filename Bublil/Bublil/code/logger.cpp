#include "logger.h"



void lg::textCol(const std::string& colour)
{
	const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attrib;

	if (colour == "WHITE")
		attrib = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
	else if(colour=="RED")
		attrib = FOREGROUND_RED;
	else if (colour == "GREEN")
		attrib = FOREGROUND_GREEN;
	else if(colour == "BLUE")
		attrib = FOREGROUND_BLUE;
	else
		{;}
	SetConsoleTextAttribute(hStdOut, attrib);
}


void lg::sayHello()
{
	std::cout << "Hello world!\n";
}

void lg::log(const std::string& message)
{
	lg::textCol("WHITE");
	std::cout << message<<'\n';
}

void lg::err(const std::string & message)
{
	lg::textCol("RED");
	std::cout << message << '\n';
}

void lg::warn(const std::string & message)
{
	lg::textCol("BLUE");
	std::cout << message << '\n';
}
