#pragma once

#include<iostream>	//Console output.
#include<string>	//General comfort.
#include<Windows.h>	//General comfort.

namespace lg
{
	namespace cwout
	{
		enum TEXT_COLOUR
		{
			TC_DARK_RED, TC_DARK_GREEN, TC_DARK_BLUE, TC_GREY,
			TC_RED, TC_GREEN, TC_BLUE, TC_WHITE,

			TC_FINALPLACEHOLDER
		};
		void textCol(const TEXT_COLOUR& tc);

		void clear();
	}
}
