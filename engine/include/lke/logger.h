#pragma once
#include <lke/lke.h>

#include <string>

namespace lke
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    lkedll void Log(LogLevel level, const std::string& message);
    lkedll void LazyEAssert(bool condition, const std::string& message);
}