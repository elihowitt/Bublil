#pragma once

#include"logger.h"

void lg::textCol(const lg::TEXT_COLOUR& tc)
{
	const HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attrib;

	switch (tc)
	{	
	case TC_DARK_RED:
		attrib = FOREGROUND_RED;
		break;
	case TC_DARK_GREEN:
		attrib = FOREGROUND_GREEN;
		break;
	case TC_DARK_BLUE:
		attrib = FOREGROUND_BLUE;
		break;
	case TC_GREY:
		attrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	case TC_RED:
		attrib =   FOREGROUND_INTENSITY | FOREGROUND_RED;
		break;
	case TC_GREEN:
		attrib =   FOREGROUND_INTENSITY | FOREGROUND_GREEN;
		break;
	case TC_BLUE:
		attrib =   FOREGROUND_INTENSITY | FOREGROUND_BLUE;
		break;
	case TC_WHITE:
		attrib =   FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
		break;
	case TC_FINALPLACEHOLDER:
	default:
		attrib = NULL;
		break;
	}
	SetConsoleTextAttribute(hStdOut, attrib);
}