#include "algebra/Matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Matrix;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = -1;
    constexpr TestType y1 = 123;
    constexpr TestType x2 = 19;
    constexpr TestType y2 = -10;

    constexpr Matrix<TestType, 2, 2> mat1 = { x1, y1, x2, y2 };

    static_assert(mat1(0, 0) == x1);
    static_assert(mat1(0, 1) == y1);
    static_assert(mat1(1, 0) == x2);
    static_assert(mat1(1, 1) == y2);

    CHECK(mat1(0, 0) == x1);
    CHECK(mat1(0, 1) == y1);
    CHECK(mat1(1, 0) == x2);
    CHECK(mat1(1, 1) == y2);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = y2;
    mat2(0, 1) = x1;
    mat2(1, 0) = y1;
    mat2(1, 1) = x2;

    CHECK(mat2(0, 0) == y2);
    CHECK(mat2(0, 1) == x1);
    CHECK(mat2(1, 0) == y1);
    CHECK(mat2(1, 1) == x2);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = -1.0;
    constexpr TestType y1 = 3123.77;
    constexpr TestType x2 = 55.12;
    constexpr TestType y2 = -10.0001;

    constexpr Matrix<TestType, 2, 2> mat1 = { x1, y1, x2, y2 };

    static_assert(mat1(0, 0) == x1);
    static_assert(mat1(0, 1) == y1);
    static_assert(mat1(1, 0) == x2);
    static_assert(mat1(1, 1) == y2);

    CHECK(mat1(0, 0) == x1);
    CHECK(mat1(0, 1) == y1);
    CHECK(mat1(1, 0) == x2);
    CHECK(mat1(1, 1) == y2);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = y2;
    mat2(0, 1) = x1;
    mat2(1, 0) = y1;
    mat2(1, 1) = x2;

    CHECK(mat2(0, 0) == y2);
    CHECK(mat2(0, 1) == x1);
    CHECK(mat2(1, 0) == y1);
    CHECK(mat2(1, 1) == x2);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;

    constexpr Matrix<TestType, 2, 2> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == zero);
}

TEMPLATE_LIST_TEST_CASE("Default constructor", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;

    constexpr Matrix<TestType, 2, 2> mat;

    static_assert(mat(0, 0) == zero);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == zero);

    CHECK(mat(0, 0) == zero);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == zero);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType zero = 0;
    constexpr TestType one  = 1;

    constexpr Matrix<TestType, 2, 2> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == one);

    CHECK(mat(0, 0) == one);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == one);
}

TEMPLATE_LIST_TEST_CASE("Constructor with diagonal coefficient", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType zero = 0.0;
    constexpr TestType one  = 1.0;

    constexpr Matrix<TestType, 2, 2> mat(one);

    static_assert(mat(0, 0) == one);
    static_assert(mat(0, 1) == zero);
    static_assert(mat(1, 0) == zero);
    static_assert(mat(1, 1) == one);

    CHECK(mat(0, 0) == one);
    CHECK(mat(0, 1) == zero);
    CHECK(mat(1, 0) == zero);
    CHECK(mat(1, 1) == one);
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 1;
    constexpr TestType y1 = 4;
    constexpr TestType x2 = 27;
    constexpr TestType y2 = 256;

    constexpr Matrix<TestType, 2, 2> mat = { x1, y1, x2, y2 };

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(1, 1) == copy1(1, 1));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(1, 1) == copy1(1, 1));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(1, 1) == copy2(1, 1));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(1, 1) == copy2(1, 1));
}

TEMPLATE_LIST_TEST_CASE("Copy operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = -18.1;
    constexpr TestType y1 = 19.2;
    constexpr TestType x2 = 20.3;
    constexpr TestType y2 = -21.4;

    constexpr Matrix<TestType, 2, 2> mat = { x1, y1, x2, y2 };

    constexpr auto copy1(mat);

    static_assert(mat(0, 0) == copy1(0, 0));
    static_assert(mat(0, 1) == copy1(0, 1));
    static_assert(mat(1, 0) == copy1(1, 0));
    static_assert(mat(1, 1) == copy1(1, 1));

    CHECK(mat(0, 0) == copy1(0, 0));
    CHECK(mat(0, 1) == copy1(0, 1));
    CHECK(mat(1, 0) == copy1(1, 0));
    CHECK(mat(1, 1) == copy1(1, 1));

    constexpr auto copy2 = mat;

    static_assert(mat(0, 0) == copy2(0, 0));
    static_assert(mat(0, 1) == copy2(0, 1));
    static_assert(mat(1, 0) == copy2(1, 0));
    static_assert(mat(1, 1) == copy2(1, 1));

    CHECK(mat(0, 0) == copy2(0, 0));
    CHECK(mat(0, 1) == copy2(0, 1));
    CHECK(mat(1, 0) == copy2(1, 0));
    CHECK(mat(1, 1) == copy2(1, 1));
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType x1 = 1;
    constexpr TestType y1 = 4;
    constexpr TestType x2 = 27;
    constexpr TestType y2 = 256;

    constexpr auto copy1(Matrix<TestType, 2, 2>({ x1, y1, x2, y2 }));

    static_assert(copy1(0, 0) == x1);
    static_assert(copy1(0, 1) == y1);
    static_assert(copy1(1, 0) == x2);
    static_assert(copy1(1, 1) == y2);

    CHECK(copy1(0, 0) == x1);
    CHECK(copy1(0, 1) == y1);
    CHECK(copy1(1, 0) == x2);
    CHECK(copy1(1, 1) == y2);

    constexpr auto copy2 = Matrix<TestType, 2, 2>({ x1, y1, x2, y2 });

    static_assert(copy2(0, 0) == x1);
    static_assert(copy2(0, 1) == y1);
    static_assert(copy2(1, 0) == x2);
    static_assert(copy2(1, 1) == y2);

    CHECK(copy2(0, 0) == x1);
    CHECK(copy2(0, 1) == y1);
    CHECK(copy2(1, 0) == x2);
    CHECK(copy2(1, 1) == y2);
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType x1 = -18.1;
    constexpr TestType y1 = 19.2;
    constexpr TestType x2 = 20.3;
    constexpr TestType y2 = -21.4;

    constexpr auto copy1(Matrix<TestType, 2, 2>({ x1, y1, x2, y2 }));

    static_assert(copy1(0, 0) == x1);
    static_assert(copy1(0, 1) == y1);
    static_assert(copy1(1, 0) == x2);
    static_assert(copy1(1, 1) == y2);

    CHECK(copy1(0, 0) == x1);
    CHECK(copy1(0, 1) == y1);
    CHECK(copy1(1, 0) == x2);
    CHECK(copy1(1, 1) == y2);

    constexpr auto copy2 = Matrix<TestType, 2, 2>({ x1, y1, x2, y2 });

    static_assert(copy2(0, 0) == x1);
    static_assert(copy2(0, 1) == y1);
    static_assert(copy2(1, 0) == x2);
    static_assert(copy2(1, 1) == y2);

    CHECK(copy2(0, 0) == x1);
    CHECK(copy2(0, 1) == y1);
    CHECK(copy2(1, 0) == x2);
    CHECK(copy2(1, 1) == y2);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][constructor]", IntegerTypes)
{
    constexpr TestType x1 = 321;
    constexpr TestType y1 = 654;
    constexpr TestType x2 = 987;
    constexpr TestType y2 = -741;

    constexpr Matrix<TestType, 2, 2> mat       = { x1, y1, x2, y2 };
    constexpr Matrix<TestType, 2, 2> identical = { x1, y1, x2, y2 };
    constexpr Matrix<TestType, 2, 2> different = { x1, y2, x2, y1 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);
    CHECK(mat != different);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][constructor]", FloatingTypes)
{
    constexpr TestType x1 = -0.1;
    constexpr TestType y1 = 0.2;
    constexpr TestType x2 = 0.3;
    constexpr TestType y2 = -0.4;

    constexpr Matrix<TestType, 2, 2> mat       = { x1, y1, x2, y2 };
    constexpr Matrix<TestType, 2, 2> identical = { x1, y1, x2, y2 };
    constexpr Matrix<TestType, 2, 2> different = { x1, y2, x2, y1 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);
    CHECK(mat != different);
}