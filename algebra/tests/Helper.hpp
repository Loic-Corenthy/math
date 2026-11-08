#pragma once

#include <cstdint>
#include <string_view>
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

    template <typename T>
    constexpr std::string_view type_name()
    {
#if defined(__clang__)
        std::string_view fun_name = __PRETTY_FUNCTION__;
        // signature: std::string_view type_name() [T = int]
        auto start = fun_name.find("T = ") + 4;
        auto end   = fun_name.rfind(']');
        return fun_name.substr(start, end - start);
#elif defined(__GNUC__)
        std::string_view fun_name = __PRETTY_FUNCTION__;
        // signature: constexpr std::string_view type_name() [with T = int]
        auto start = fun_name.find("with T = ") + 9;
        auto end   = fun_name.rfind(']');
        return fun_name.substr(start, end - start);
#elif defined(_MSC_VER)
        std::string_view fun_name = __FUNCSIG__;
        // signature: class std::basic_string_view<...> __cdecl type_name<int>(void)
        auto start = fun_name.find("type_name<") + 10;
        auto end   = fun_name.rfind(">(void)");
        return fun_name.substr(start, end - start);
#endif
    }

}  // namespace LCNS
