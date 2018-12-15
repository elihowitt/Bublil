#include"loggerMessages.h"

int main()
{
	lg::cwout::sayHello();
	lg::dbout::basicLog(L"Hello output window");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	lg::dbout::basicLog(L"Bob`n Fop`n");
	while (true)
	{
		Sleep(1000);
		lg::cwout::warn("Bob`n!!!");
	}
	std::cin.get();

	return 0;
}