#pragma once

#include <concepts>
#include <type_traits>

template <typename T>
concept Coordinate = requires(T type)
{
    std::is_arithmetic_v<T>;
    std::is_trivially_copyable_v<T>;
};