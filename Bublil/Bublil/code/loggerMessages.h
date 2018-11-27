#pragma once

#include<iostream>	//Console output.
#include<string>	//General comfort.
#include<Windows.h>	//General comfort.
#include<sstream>	//DBout.

namespace lg
{
	namespace cwout//Console window outpute(written to standard console window).
	{
		void sayHello();

		void generalLog(const std::string& type,   //For general use , and as a template for other loggers.
						const std::string& detail);//Outputs in "T = *hh::mm::ss* [type]: detail".
																			
		void basicLog(const std::string& message);
		void err(const std::string& message);
		void warn(const std::string& message);

	}
	namespace dbout//Debug output (written to output 'window').
	{
		void basicLog(const WCHAR *s);
	}
}
