#pragma once

#include<iostream>	//Console output.
#include<conio.h>	//Change colour.
#include<string>	//General comfort.
#include<Windows.h>	//General comfort.
#include<map>		//Standard map.

/*
TO_DO:
	Fix the wierd convension of the 'colour' param for 'texCol'.
	Add more colours to 'texCol'.

	Add time logging.
*/

namespace lg
{
	void sayHello();



	void textCol(const std::string& colour);
	

	void log(const std::string& message);
	void err(const std::string& message);
	void warn(const std::string& message);

}
