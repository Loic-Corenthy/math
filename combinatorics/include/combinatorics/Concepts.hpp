#pragma once

#include <concepts>

// clang-format off
template <typename T>
concept Container = requires(T container)
{
    container.size();   // must have c.size()
    container.begin();  // and c.begin()
    container.end();    // and c.end()
};
// clang-format on
