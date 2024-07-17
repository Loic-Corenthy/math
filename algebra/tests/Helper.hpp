#pragma once

namespace LCNS
{
    template <typename T>
    constexpr T epsilonVeryLowPrecision()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 1e-3f;
        }
        else if (std::is_same_v<T, double>)
        {
            return 1e-5;
        }
    }

    template <typename T>
    constexpr T epsilonLowPrecision()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 1e-3f;
        }
        else if (std::is_same_v<T, double>)
        {
            return 1e-6;
        }
    }

    template <typename T>
    constexpr T epsilonHighPrecision()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 1e-6f;
        }
        else if (std::is_same_v<T, double>)
        {
            return 1e-9;
        }
    }
}  // namespace LCNS
