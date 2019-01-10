#include"logger.h"

void lg::cwout::sayHello()
{
	std::string str("Hello world!");
	for (char c : str)
	{
		switch (rand()%8)
		{	
		case 0:
			lg::cwout::textCol(TEXT_COLOUR::TC_DARK_RED);
			break;
		case 1:
			lg::cwout::textCol(TEXT_COLOUR::TC_DARK_GREEN);
			break;
		case 2:
			lg::cwout::textCol(TEXT_COLOUR::TC_DARK_BLUE);
			break;
		case 3:
			lg::cwout::textCol(TEXT_COLOUR::TC_RED);
			break;
		case 4:
			lg::cwout::textCol(TEXT_COLOUR::TC_GREEN);
			break;
		case 5:
			lg::cwout::textCol(TEXT_COLOUR::TC_BLUE);
			break;
		case 6:
			lg::cwout::textCol(TEXT_COLOUR::TC_GREY);
			break;
		case 7:
			lg::cwout::textCol(TEXT_COLOUR::TC_WHITE);
			break;
		}
		std::cout << c;
	}
	std::cout << '\n';
	//lg::cwout::textCol(TEXT_COLOUR::TC_WHITE);
	//std::cout << "Hello world!\n";
}

void lg::cwout::generalLog(const std::string & type, const std::string & detail)
{
	lg::cwout::textCol(TEXT_COLOUR::TC_WHITE);
	std::cout << "T = " << lg::getTime() << "   [" << type << "]: " << detail << '\n';
}

void lg::cwout::basicLog(const std::string& message)
{
	lg::cwout::textCol(TEXT_COLOUR::TC_WHITE);
	std::cout << message<<'\n';
}

void lg::cwout::err(const std::string & message)
{
	lg::cwout::textCol(TEXT_COLOUR::TC_RED);
	lg::cwout::generalLog("ERROR", message);
}

void lg::cwout::warn(const std::string & message)
{
	lg::cwout::textCol(TEXT_COLOUR::TC_DARK_RED);
	lg::cwout::generalLog("WARN", message);
}


//End of 'cwout' namespace definitions.
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
///		    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
///		    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
///		    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
/////////// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~;
//Start of 'dbout' namespace definitions.

void lg::dbout::basicLog(const WCHAR* s)
{
	std::wostringstream os;
	os << s << L'\n';
	OutputDebugStringW(os.str().c_str());
}