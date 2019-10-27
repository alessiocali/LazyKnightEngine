#include <lazye/logger.h>

#include <iostream>

namespace lazye
{
	std::string GetLogLevelName(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Info:
			return "Info";
		case LogLevel::Warning:
			return "Warning";
		case LogLevel::Error:
			return "Error";
		default:
			LazyEAssert(false, "Unrecognized LogLevel value");
			return "Unknown";
		}
	}

	void Log(LogLevel level, const std::string& message)
	{
		std::cout << GetLogLevelName(level) << " " << message << std::endl;
	}

	void LazyEAssert(bool condition, const std::string& message)
	{
		if (!condition)
		{
			Log(LogLevel::Error, message);
			exit(1);
		}
	}
}