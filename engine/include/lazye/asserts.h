#pragma once

#include <cassert>

namespace lazye
{
#pragma warning(push)
#pragma warning(disable : 4100)

    template <typename ConditionType, typename StringType, typename... Args>
    void Assert(ConditionType condition, StringType message, Args... args)
    {
#ifdef NDEBUG
        std::cerr << message << ... << args << endl;
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