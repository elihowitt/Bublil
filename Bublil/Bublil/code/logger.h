#pragma once

#include<iostream>	//Console output.
#include<conio.h>	//Change colour.
#include<string>	//General comfort.
#include<Windows.h>	//General comfort.

/*
TO_DO:
	Add more colours to 'texCol'.

	Add time logging.

	Add nice formating.
*/

namespace lg
{
	void sayHello();

	enum TEXT_COLOUR
	{
		TC_DARK_RED, TC_DARK_GREEN, TC_DARK_BLUE, TC_GREY,
		TC_RED, TC_GREEN, TC_BLUE, TC_WHITE,

		TC_FINALPLACEHOLDER
	};
	void textCol(const TEXT_COLOUR& tc);
	

	void log(const std::string& message);
	void err(const std::string& message);
	void warn(const std::string& message);

}
