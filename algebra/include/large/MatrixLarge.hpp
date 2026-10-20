#pragma once

#include "algebra/Internal.hpp"
#include <cstdlib>

namespace LCNS::large
{
    template <Coordinate coordinate, unsigned int rows, unsigned int cols>
#if defined(AVX512_ENABLED)
    class alignas(64) MatrixLarge
#elif defined(AVX2_ENBALED)
    class alignas(32) MatrixLarge
#else
    class MatrixLarge
#endif
    {
    public:
        constexpr MatrixLarge() = default;

    private:
        consteval unsigned int paddedRows()
        {
            constexpr auto numElements = static_cast<int>(64 / sizeof(coordinate));
            constexpr auto res         = std::div(static_cast<int>(rows), numElements);

            return (res.quot + 1) * numElements;
        }

    private:
    };

}
