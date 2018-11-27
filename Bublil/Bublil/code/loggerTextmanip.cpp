#pragma once

#include"loggerTextmanip.h"

void lg::cwout::textCol(const lg::cwout::TEXT_COLOUR& tc)
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

void lg::cwout::clear()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}