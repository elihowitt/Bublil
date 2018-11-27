#include<SDL2\SDL.h>

#include "loggerMessages.h"
#include"loggerTextmanip.h"
#include"loggerUtil.h"


void lg::cwout::sayHello()
{
	std::cout << "Hello world!\n";
}

void lg::cwout::generalLog(const std::string & type, const std::string & detail)
{
	std::cout << "T = " << lg::getTime(SDL_GetTicks()) << "   [" << type << "]: " << detail << '\n';
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