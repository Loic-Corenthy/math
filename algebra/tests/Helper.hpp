#pragma once

#include <cstdint>
#include <type_traits>

namespace LCNS
{
    template <typename T>
    constexpr T epsilonVeryLowPrecision()
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return 1e-3F;
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
            return 1e-3F;
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
            return 1e-6F;
        }
        else if (std::is_same_v<T, double>)
        {
            return 1e-9;
        }
    }


    template <typename Numeric, unsigned int rows, unsigned int cols>
    consteval std::size_t precomputedSize()
    {
        if constexpr (std::is_same_v<Numeric, int32_t> and (cols <= 16))
        {
            return rows * 16;
        }
        else if constexpr (std::is_same_v<Numeric, int32_t> and cols <= 32)
        {
            return rows * 32;
        }
        else
        {
            static_assert(false, "Unsupported case");
        }
    }

}  // namespace LCNS
