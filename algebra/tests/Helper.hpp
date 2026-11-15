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
        // Avoid to use the same modulo computation as in the MatrixLarge class

        if constexpr (std::is_same_v<Numeric, int32_t>)
        {
            if constexpr (cols <= 16)
            {
                return rows * 16;
            }
            else if constexpr (cols <= 32)
            {
                return rows * 32;
            }
            else
            {
                static_assert(false, "Unsupported size");
            }
        }
        else if constexpr (std::is_same_v<Numeric, float>)
        {
            if constexpr (cols <= 16)
            {
                return rows * 16;
            }
            else if constexpr (cols <= 32)
            {
                return rows * 32;
            }
            else
            {
                static_assert(false, "Unsupported size");
            }
        }
        else if constexpr (std::is_same_v<Numeric, double>)
        {
            if constexpr (cols <= 8)
            {
                return rows * 8;
            }
            else if constexpr (cols <= 16)
            {
                return rows * 16;
            }
            else if constexpr (cols <= 24)
            {
                return rows * 24;
            }
            else
            {
                static_assert(false, "Unsupported size");
            }
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
        // signature: std::string_view type_name() [T = int; ...]
        std::string_view fun_name = __PRETTY_FUNCTION__;

        auto start = fun_name.find("T = ") + 4;
        auto end   = fun_name.rfind(';');
#elif defined(__GNUC__)
        // signature: constexpr std::string_view type_name() [with T = int; ...]
        std::string_view fun_name = __PRETTY_FUNCTION__;

        auto start = fun_name.find("with T = ") + 9;
        auto end   = fun_name.rfind(';');
#elif defined(_MSC_VER)
        // signature: class std::basic_string_view<...> __cdecl type_name<int>(void)
        std::string_view fun_name = __FUNCSIG__;

        auto start = fun_name.find("type_name<") + 10;
        auto end   = fun_name.rfind(">(void)");
#endif

        return fun_name.substr(start, end - start);
    }

}  // namespace LCNS
