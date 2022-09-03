#include "algebra/Matrix.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using LCNS::Algebra::Matrix;

using IntegerTypes  = std::tuple<short, int, long>;
using FloatingTypes = std::tuple<float, double, long double>;

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = -1;
    constexpr TestType m01 = 123;
    constexpr TestType m10 = 19;
    constexpr TestType m11 = -10;

    constexpr Matrix<TestType, 2, 2> mat1 = { m00, m01, m10, m11 };

    static_assert(mat1(0, 0) == m00);
    static_assert(mat1(0, 1) == m01);
    static_assert(mat1(1, 0) == m10);
    static_assert(mat1(1, 1) == m11);

    CHECK(mat1(0, 0) == m00);
    CHECK(mat1(0, 1) == m01);
    CHECK(mat1(1, 0) == m10);
    CHECK(mat1(1, 1) == m11);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = m11;
    mat2(0, 1) = m00;
    mat2(1, 0) = m01;
    mat2(1, 1) = m10;

    CHECK(mat2(0, 0) == m11);
    CHECK(mat2(0, 1) == m00);
    CHECK(mat2(1, 0) == m01);
    CHECK(mat2(1, 1) == m10);
}

TEMPLATE_LIST_TEST_CASE("Accessor operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -1.0;
    constexpr TestType m01 = 3123.77;
    constexpr TestType m10 = 55.12;
    constexpr TestType m11 = -10.0001;

    constexpr Matrix<TestType, 2, 2> mat1 = { m00, m01, m10, m11 };

    static_assert(mat1(0, 0) == m00);
    static_assert(mat1(0, 1) == m01);
    static_assert(mat1(1, 0) == m10);
    static_assert(mat1(1, 1) == m11);

    CHECK(mat1(0, 0) == m00);
    CHECK(mat1(0, 1) == m01);
    CHECK(mat1(1, 0) == m10);
    CHECK(mat1(1, 1) == m11);

    Matrix<TestType, 2, 2> mat2;
    mat2(0, 0) = m11;
    mat2(0, 1) = m00;
    mat2(1, 0) = m01;
    mat2(1, 1) = m10;

    CHECK(mat2(0, 0) == m11);
    CHECK(mat2(0, 1) == m00);
    CHECK(mat2(1, 0) == m01);
    CHECK(mat2(1, 1) == m10);
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
    constexpr TestType m00 = 1;
    constexpr TestType m01 = 4;
    constexpr TestType m10 = 27;
    constexpr TestType m11 = 256;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

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
    constexpr TestType m00 = -18.1;
    constexpr TestType m01 = 19.2;
    constexpr TestType m10 = 20.3;
    constexpr TestType m11 = -21.4;

    constexpr Matrix<TestType, 2, 2> mat = { m00, m01, m10, m11 };

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
    constexpr TestType m00 = 1;
    constexpr TestType m01 = 4;
    constexpr TestType m10 = 27;
    constexpr TestType m11 = 256;

    constexpr auto copy1(Matrix<TestType, 2, 2>({ m00, m01, m10, m11 }));

    static_assert(copy1(0, 0) == m00);
    static_assert(copy1(0, 1) == m01);
    static_assert(copy1(1, 0) == m10);
    static_assert(copy1(1, 1) == m11);

    CHECK(copy1(0, 0) == m00);
    CHECK(copy1(0, 1) == m01);
    CHECK(copy1(1, 0) == m10);
    CHECK(copy1(1, 1) == m11);

    constexpr auto copy2 = Matrix<TestType, 2, 2>({ m00, m01, m10, m11 });

    static_assert(copy2(0, 0) == m00);
    static_assert(copy2(0, 1) == m01);
    static_assert(copy2(1, 0) == m10);
    static_assert(copy2(1, 1) == m11);

    CHECK(copy2(0, 0) == m00);
    CHECK(copy2(0, 1) == m01);
    CHECK(copy2(1, 0) == m10);
    CHECK(copy2(1, 1) == m11);
}

TEMPLATE_LIST_TEST_CASE("Move operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -18.1;
    constexpr TestType m01 = 19.2;
    constexpr TestType m10 = 20.3;
    constexpr TestType m11 = -21.4;

    constexpr auto copy1(Matrix<TestType, 2, 2>({ m00, m01, m10, m11 }));

    static_assert(copy1(0, 0) == m00);
    static_assert(copy1(0, 1) == m01);
    static_assert(copy1(1, 0) == m10);
    static_assert(copy1(1, 1) == m11);

    CHECK(copy1(0, 0) == m00);
    CHECK(copy1(0, 1) == m01);
    CHECK(copy1(1, 0) == m10);
    CHECK(copy1(1, 1) == m11);

    constexpr auto copy2 = Matrix<TestType, 2, 2>({ m00, m01, m10, m11 });

    static_assert(copy2(0, 0) == m00);
    static_assert(copy2(0, 1) == m01);
    static_assert(copy2(1, 0) == m10);
    static_assert(copy2(1, 1) == m11);

    CHECK(copy2(0, 0) == m00);
    CHECK(copy2(0, 1) == m01);
    CHECK(copy2(1, 0) == m10);
    CHECK(copy2(1, 1) == m11);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][operator]", IntegerTypes)
{
    constexpr TestType m00 = 321;
    constexpr TestType m01 = 654;
    constexpr TestType m10 = 987;
    constexpr TestType m11 = -741;

    constexpr Matrix<TestType, 2, 2> mat       = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> identical = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> different = { m00, m11, m10, m01 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);
    CHECK(mat != different);
}

TEMPLATE_LIST_TEST_CASE("Comparision operator", "[algebra][matrix][dim2][operator]", FloatingTypes)
{
    constexpr TestType m00 = -0.1;
    constexpr TestType m01 = 0.2;
    constexpr TestType m10 = 0.3;
    constexpr TestType m11 = -0.4;

    constexpr Matrix<TestType, 2, 2> mat       = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> identical = { m00, m01, m10, m11 };
    constexpr Matrix<TestType, 2, 2> different = { m00, m11, m10, m01 };

    static_assert(mat == identical);
    static_assert(mat != different);

    CHECK(mat == identical);
    CHECK(mat != different);
}