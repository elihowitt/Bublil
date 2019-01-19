#include"logger.h"

lg::fout::fout()
{
	runtimeEventFile = std::ofstream("./loggings/runtimeEvents.txt");
	resultFile = std::ofstream("./loggings/results.txt");
}

lg::fout::~fout()
{
	runtimeEventFile.close();
	resultFile.close();
	std::ifstream res("./loggings/results.txt");
	std::wstring str((std::istreambuf_iterator<char>(res)),
		std::istreambuf_iterator<char>());

	lg::dbout::basicLog(str.c_str());
	res.close();
}

void lg::fout::logRuntimeEvent(const std::string& type, const std::string& detail)
{
	if(runtimeEventFile.is_open())
	runtimeEventFile << "T = " << lg::getTime() << "   [" << type << "]: " << detail << '\n';
}

void lg::fout::logResults(const std::string& data)
{
	if (resultFile.is_open())
		resultFile << data;
}
