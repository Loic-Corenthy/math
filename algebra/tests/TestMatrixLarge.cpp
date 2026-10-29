#include "large/MatrixLarge.hpp"

#include "Helper.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

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

    TEMPLATE_TEST_CASE_SIG("KeyValueStore private members can be accessed via friend fixture",
                           "[template][fixture][product]",
                           ((Coordinate coordinate, unsigned int rows, unsigned int cols), coordinate, rows, cols),
                           (int32_t, 3, 4),
                           (int32_t, 3, 16),
                           (int32_t, 3, 25))
    {
        MatrixLarge<coordinate, rows, cols> mat;


        SECTION("Check the internal size of the array containing the coefficients")
        {
            const auto expectedSize = LCNS::precomputedSize<coordinate, rows, cols>();
            CHECK(Access::coeffs(mat).size() == expectedSize);
        }
    }

}
