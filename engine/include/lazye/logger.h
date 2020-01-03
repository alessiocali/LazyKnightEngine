#pragma once
#include <lazye/lazye.h>

#include <string>

namespace lazye
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    lazyedll void Log(LogLevel level, const std::string& message);
    lazyedll void LazyEAssert(bool condition, const std::string& message);
}