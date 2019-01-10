#pragma once

#include<iostream>	//Console output.
#include<string>	//General comfort.
#include<Windows.h>	//General comfort.
#include<sstream>	//DBout.
#include<fstream>	//Fout.

namespace lg
{
	std::string getTime();
	std::string getTimeByMilliseconds(const long int& milliseconds);

	namespace cwout//Console window outpute(written to standard console window).
	{
		enum TEXT_COLOUR
		{
			TC_DARK_RED, TC_DARK_GREEN, TC_DARK_BLUE, TC_GREY,
			TC_RED, TC_GREEN, TC_BLUE, TC_WHITE,

			TC_FINALPLACEHOLDER
		};
		void textCol(const TEXT_COLOUR& tc);

		void clear();

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
	class fout
	{
	public:
		fout();
		~fout();
		void logRuntimeEvent(const std::string& type, const std::string& detail); //logs like 'generalLog'
																				  //To 'logging/runtimEvents.txt'.
		void logResults(const std::string& data);//Used to log the end-results of running the program.
												 //Logs to 'loggings/results.txt'.

	private:
		std::ofstream runtimeEventFile, resultFile;
	};
}