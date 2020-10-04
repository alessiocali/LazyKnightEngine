#pragma once

#include <cassert>
#include <iostream>

namespace lke
{
#pragma warning(push)
#pragma warning(disable : 4100)

    template <typename ConditionType, typename StringType, typename... Args>
    void Assert(ConditionType condition, StringType message, Args... args)
    {
#ifndef NDEBUG
        if (!condition)
        {
            ((std::cerr << message) << ... << args) << std::endl;
        }
        
        assert(condition);
#endif // NDEBUG
    }

#pragma warning(pop)

    template <typename ConditionType>
    void Assert(ConditionType condition)
    {
        Assert(condition, "");
    }
}