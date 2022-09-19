#pragma once

namespace LCNS
{
    template <typename T>
    constexpr T compileTimeEpsilon()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 0.001f;
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return 0.000'001;
        }
        else if constexpr (std::is_same_v<T, long double>)
        {
            return 0.000'000'001;
        }
    }

    template <typename T>
    constexpr T runTimeEpsilon()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 0.000'01f;
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return 0.000'000'001;
        }
        else if constexpr (std::is_same_v<T, long double>)
        {
            return 0.000'000'000'001;
        }
    }
}  // namespace LCNS
