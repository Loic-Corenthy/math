#include "algebra/Internal.hpp"
#include "large/MatrixLarge.hpp"

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
                           (int, 3, 4),
                           (int, 9, 13))
    {  // Check size first
        MatrixLarge<int, 4, 3> mat;

        SECTION("Check the internal size of the array containing the coefficients")
        { CHECK(Access::coeffs(mat).size() == 16); }
    }

    // TEMPLATE_TEST_CASE_METHOD(MatrixLargeTestPeer, "Default constructor", "[large][matrix][padding]", (int, 3, 4))
    // {
    //     MatrixLarge<int, 3, 4> mat;
    //
    //     // You can call the helper method inherited from the fixture
    //     CHECK(internalSize(mat) == (64 / 4) * 4);
    // }

}
