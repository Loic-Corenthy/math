#include "large/MatrixLarge.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#ifdef AVX_ENABLED_ON_CPU
#include <immintrin.h>
#endif

#include <print>

namespace LCNS::large
{
    struct MatrixLargeTestAccess
    {
        template <Coordinate coordinate, unsigned int rows, unsigned int cols>
        static auto& coeffs(MatrixLarge<coordinate, rows, cols>& mat)
        {
            // Jsut return the array of coefficients
            return mat._coeff;
        }
    };

    using Access = MatrixLargeTestAccess;

    TEMPLATE_TEST_CASE_SIG("Check internal matrix size",
                           "[template][fixture][product]",
                           ((Coordinate coordinate, unsigned int rows, unsigned int cols), coordinate, rows, cols),
                           (int32_t, 3, 4),
                           (int32_t, 3, 16),
                           (int32_t, 3, 25),
                           (float, 3, 5),
                           (float, 123, 16),
                           (float, 17, 25),
                           (double, 2, 7),
                           (double, 3, 8),
                           (double, 4, 20))
    {
        MatrixLarge<coordinate, rows, cols> mat;


        SECTION("Check the internal size of the array containing the coefficients")
        {
            const auto expectedSize = LCNS::precomputedSize<coordinate, rows, cols>();
            const auto name         = LCNS::type_name<coordinate>();
            std::println("For a matrix <{},{},{}>, the reserved memory is for {} elements", name, rows, cols, expectedSize);
            CHECK(Access::coeffs(mat).size() == expectedSize);
        }
    }


    TEMPLATE_TEST_CASE_SIG("Check using load for aligned memory",
                           "[template][fixture][product]",
                           ((Coordinate coordinate, unsigned int rows, unsigned int cols), coordinate, rows, cols),
                           (int32_t, 3, 4))
    {
        MatrixLarge<coordinate, rows, cols> mat;

        for (size_t i{}; i < rows; ++i)
        {
            for (size_t j{}; j < cols; ++j)
            {
                mat(i, j) = 1;
            }
        }

        SECTION("Check loading aligned memory")
        {
            coordinate sum{};
            for (size_t i{}; i < rows; ++i)
            {
                __m512i chunk = _mm512_load_epi32(mat.data());
                // sum += __mm512_
            }
        }
    }
}
