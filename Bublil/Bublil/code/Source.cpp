#include "logger.h"

int main()
{
	lg::sayHello();
	lg::log("LOG- Bob`n!!");
	lg::err("ERR- Bob`n!!");
	lg::warn("WARN- Bob`n!!");
	while (1);
	return 31;
}