#include"loggerMessages.h"
#include"loggerUtil.h"

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
	lg::cwout::warn("Bob`n!!!");

	std::cin.get();

	return 0;
}