#include "algebra/Matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Matrix;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][vector][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = -1;
    constexpr TestType y1 = 123;
    constexpr TestType x2 = 19;
    constexpr TestType y2 = -10;

    constexpr Matrix<TestType, 2, 2> mat({ x1, y1, x2, y2 });

    static_assert(mat(0, 0) == x1);
    static_assert(mat(0, 1) == y1);
    static_assert(mat(1, 0) == x2);
    static_assert(mat(1, 1) == y2);

    CHECK(mat(0, 0) == x1);
    CHECK(mat(0, 1) == y1);
    CHECK(mat(1, 0) == x2);
    CHECK(mat(1, 1) == y2);
}