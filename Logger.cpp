#include "Logger.h"
#include <ctime>
Logger::Logger() {
	std::time_t now = std::time(nullptr);
	std::tm* localTime = std::localtime(&now);
	path = std::put_time(localTime, "%Y-%m-%d_%H:%M:%S");

}