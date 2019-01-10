#include"logger.h"

#include<SDL2\SDL.h>

std::string lg::getTime()
{
	return getTimeByMilliseconds(SDL_GetTicks());
}

std::string lg::getTimeByMilliseconds(const long int & milliseconds)
{
	std::string str;

	int seconds = milliseconds / 1000, minutes = 0, hours = 0;
	while (seconds >= 60)
	{
		seconds -= 60;
		minutes++;
	}
	while (minutes >= 60)
	{
		minutes -= 60;
		hours += 1;
	}
	hours %= 24;
	//Now all the numbers are right.

	//Now add to string in correct format.
	if (hours < 10)
		str += '0';
	str += std::to_string(hours);
	str += "::";

	if (minutes < 10)
		str += '0';
	str += std::to_string(minutes);
	str += "::";

	if (seconds < 10)
		str += '0';
	str += std::to_string(seconds);

	return std::string(str);
}